#include "FunctionCall.h"
#include "BuildTypes.h"
#include "FunctionDecl.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "Load.h"
#include "BackLLVM.h"
#include "UserType.h"
#include "Program.h"
#include "Interface.h"
#include "semantic/PropagateTypes.h"
#include "semantic/Visitor.h"

extern Program *program;

Node* FunctionCall::getSymbol() {
    if (dt == BuildTypes::undefinedType)
        getDataType();
    return symbol;
}

DataType FunctionCall::getDataType() {
    
    if (dt == BuildTypes::undefinedType) {
        // is a constructor?
        dt = buildTypes->getType(ident.getFullName());
        if (node_children.size() <= 1 && dt != BuildTypes::undefinedType) {
            symbol = findSymbol(buildTypes->name(dt));
            return dt;
        }

        if (!symbol) {
            if (stem) {
                // method of a user type
                symbol = findSymbol(buildTypes->name(stem->getDataType()));
                symbol = symbol->findMember(ident.getFullName());
            } else {
                symbol = ident.getSymbol(getScope());
            }
        }

        if (symbol)
            dt = symbol->getDataType();
    }
    return dt;
}

int FunctionCall::getNumCodedParams() {
    int result = node_children.size();
    if (stem)
        return result--;
    return result;
}

Value *FunctionCall::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

    RobDbgInfo.emitLocation(this);
    string name = ident.getFullName();

    if (!symbol)
        getDataType();

    if (!symbol) {
        yyerrorcpp("Function " + name + " not defined.", this);
        return NULL;
    }

    FunctionBase *fsymbol = dynamic_cast<FunctionBase*>(symbol);
    if (fsymbol == NULL) {
        yyerrorcpp("Symbol " + name + " is not a function.", this);
        return NULL;
    } else if (ident.isComplex()) {
        if (Interface *intf = dynamic_cast<Interface*>(stem)) {
            yyerrorcpp("Can not call an interface function.", this);
            return NULL;
        }
    }

    if (fsymbol->getNumCodedParams() != getNumCodedParams()) {
        yyerrorcpp(string_format("Function %s has %d argument(s) but was called with %d.",
            name.c_str(), fsymbol->getNumCodedParams(), 
            getNumCodedParams()), this);
        yywarncpp("The function declaration is here.", symbol);
        return NULL;
    }

    // skip calling onlydebug functions when not debugging
    if (!debug_info && fsymbol->getAttributes()->hasAttribute(fa_debugonly))
        return NULL;

    Builder->SetInsertPoint(block);

    vector<Value*> args;
    vector<DataType> dataTypes;
    int paramId = 0;
    for (Node *param : node_children) {
        DataType call_dt = param->getDataType();
        DataType def_dt = fsymbol->getParameters().getParamType(paramId);
        string argName = fsymbol->getParameters().getParamName(paramId);

        Value *valor = param->generateNewBlock(func, &block, allocblock);
        if (!valor) {
            yyerrorcpp(string_format("The value for argument %s is undefined.", argName.c_str()), param);
            return NULL;
        }
        Builder->SetInsertPoint(block);

        if (buildTypes->isArrayOrMatrix(call_dt)) {
            // we pass the address of the first element
            Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
            Value *indexList[2] = {zero, zero};
            Value *ptr = Builder->CreateGEP(param->getLLVMType(), valor, ArrayRef<Value*>(indexList), "gep");
            valor = ptr;
        }

        args.insert(args.begin() + paramId, valor);
        dataTypes.insert(dataTypes.begin() + paramId, def_dt);

        // add a size parameter after each array, or .rows and .cols for matrixes
        if (buildTypes->isArrayOrMatrix(call_dt)) {
            vector<string> params;
            if (buildTypes->isArray(call_dt))
                params.push_back(".size");
            else if (buildTypes->isMatrix(call_dt)) {
                params.push_back(".rows");
                params.push_back(".cols");
            }

            for(const string& p: params) {
                Node *coerced;
                Value *value = NULL;
                Node *size = param->findMember("size");
                if (size) {
                    coerced = PropagateTypes::coerceTo(size, tint32u);
                    value = coerced->generateNewBlock(func, &block, allocblock);
                }
                if (!value) {
                    string pname = param->getName() + p;
                    Load ld(Identifier(pname, param->getLoc()));
                    ld.setScope(func);
                    coerced = PropagateTypes::coerceTo(&ld, tint32u);
                    value = coerced->generateNewBlock(func, &block, allocblock);
                }
                assert(value != NULL && "must pass the array size.");
                args.push_back(value);
                dataTypes.push_back(coerced->getDataType());
            }
        }

        paramId++;
    }

    // this parameter at the end
    if (stem) {
        Value *stemValue = stem->generateNewBlock(func, &block, allocblock);
        args.push_back(stemValue);
        dataTypes.push_back(stem->getDataType());
    } else if (fsymbol->getThisArgDt() != BuildTypes::undefinedType) {
        // calling a function of the type itself, without stem
        Value *thisPointer = func->getThisArg();
        DataType thisDt = func->getThisArgDt();
        Type *thisTy = buildTypes->llvmType(thisDt);
        Value *ptr = Builder->CreateLoad(PointerType::getUnqual(thisTy), thisPointer, "derefthis");
        args.push_back(ptr);
        dataTypes.push_back(fsymbol->getThisArgDt());
    }

    ArrayRef<Value*> argsRef(args);

    Builder->SetInsertPoint(allocblock);
    Value *vfunc = symbol->getLLVMValue(func);
    assert(vfunc && "Need a function to call.");
    Function *cfunc = dyn_cast<Function>(vfunc);

    // symbol->getLLVMValue above can emit another location (preGenerate of the 
    // function being called), so we emit location again
    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);

    // calling an interface function; will use the dispatcher
    if (stem && buildTypes->isInterface(stem->getDataType())) {
        string func_full_name = string_format("%s:%s",
            buildTypes->name(stem->getDataType()),
            ident.getFullName().c_str());

        Function *intf_cfunc = mainmodule->getFunction(func_full_name);
        if (!intf_cfunc) {
            intf_cfunc = Function::Create(cfunc->getFunctionType(), Function::ExternalLinkage, 
                codeAddrSpace, func_full_name, mainmodule);
            intf_cfunc->setCallingConv(CallingConv::C);
            intf_cfunc->addFnAttr(Attribute::AlwaysInline);
        }
        cfunc = intf_cfunc;
    }

    CallInst *call = Builder->CreateCall(cfunc, argsRef);
    
    // set signedness
    if (cfunc->hasRetAttribute(Attribute::ZExt))
        call->addRetAttr(Attribute::ZExt);  
    int i = 0;
    for(DataType adt : dataTypes) {
        if (buildTypes->isUnsignedDataType(adt))
			call->addParamAttr(i, Attribute::ZExt);
        i++;
    }

    return call;
}

Node* FunctionCall::accept(Visitor& v) {
    return v.visit(*this);
}
