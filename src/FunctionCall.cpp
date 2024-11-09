#include "FunctionCall.h"
#include "BuildTypes.h"
#include "FunctionDecl.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "PropagateTypes.h"
#include "Load.h"
#include "Visitor.h"
#include "BackLLVM.h"
#include "UserType.h"
#include "Program.h"
#include "Interface.h"

extern Program *program;

DataType FunctionCall::getDataType() {
    
    if (dt == BuildTypes::undefinedType) {
        // is a constructor? this can occur while running PropagateTypes.
        dt = buildTypes->getType(ident.getFullName());
        if (node_children.size() <= 1 && dt != BuildTypes::undefinedType) {
            return dt;
        }

        if (!symbol)
            symbol = ident.getSymbol(getScope());

        if (symbol)
            dt = symbol->getDataType();
    }
    return dt;
}

Value *FunctionCall::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

    RobDbgInfo.emitLocation(this);
    string name = ident.getFullName();

    if (!symbol)
        symbol = ident.getSymbol(getScope(), false);

    if (symbol == NULL) {
        yyerrorcpp("Function " + name + " not defined.", this);
        return NULL;
    }

    FunctionBase *fsymbol = dynamic_cast<FunctionBase*>(symbol);
    if (fsymbol == NULL) {
        yyerrorcpp("Symbol " + name + " is not a function.", this);
        return NULL;
    } else if (ident.isComplex()) {
        Node *stem = ident.getStem().getSymbol(getScope());
        if (Interface *intf = dynamic_cast<Interface*>(stem)) {
            yyerrorcpp("Can not call an interface function.", this);
            return NULL;
        }
    }

    if (fsymbol->getNumCodedParams() != node_children.size()) {
        yyerrorcpp(string_format("Function %s has %d argument(s) but was called with %d.",
            name.c_str(), fsymbol->getNumCodedParams(), 
            node_children.size()), this);
        yywarncpp("The function declaration is here.", symbol);
        return NULL;
    }

    // skip calling onlydebug functions when not debugging
    if (!debug_info && fsymbol->getAttributes()->hasAttribute(fa_debugonly))
        return NULL;

    dt = fsymbol->getDataType();

    Node *stemSymbol = NULL;
    Value *stem = func->getThisArg();
    DataType stemdt = func->getThisArgDt();

    Builder->SetInsertPoint(block);
    if (ident.isComplex()) {
        Identifier istem = ident.getStem();
        stemSymbol = istem.getSymbol(getScope());
        stem = stemSymbol->getLLVMValue(func);
        stemdt = stemSymbol->getDataType();
        
        // TODO: When accessing a.x.func(), need to load a and gep x
        //Load loadstem(ident.getStem());
        //loadstem.setParent(this->parent);
        //stem = loadstem.generate(func, block, allocblock);
    }

    vector<Value*> args;
    vector<DataType> dataTypes;
    int paramId = 0;
    for (Node *param : node_children) {
        DataType call_dt = param->getDataType();
        DataType def_dt = fsymbol->getParameters().getParamType(paramId);
        string argName = fsymbol->getParameters().getParamName(paramId);

        Value *valor = param->generate(func, block, allocblock);
        if (!valor) {
            yyerrorcpp(string_format("The value for argument %s is undefined.", argName.c_str()), param);
            return NULL;
        } else {
            // A distinct block can return from boolean short-circuit evaluation
            Instruction* instr = dyn_cast<Instruction>(valor);
            if (instr && instr->getParent() != allocblock) {
                block = instr->getParent();
                Builder->SetInsertPoint(block);
            }
        }

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
                Value *value;
                Node *size = param->findMember("size");
                if (size) {
                    coerced = PropagateTypes::coerceTo(size, tint32u);
                    value = coerced->generate(func, block, allocblock);
                } else {
                    string pname = param->getName() + p;
                    Load ld(Identifier(pname, param->getLoc()));
                    ld.setScope(func);
                    coerced = PropagateTypes::coerceTo(&ld, tint32u);
                    value = coerced->generate(func, block, allocblock);
                }
                args.push_back(value);
                dataTypes.push_back(coerced->getDataType());
            }
        }

        paramId++;
    }

    // this parameter
    if (stemSymbol) {
        if (stemSymbol->isPointerToPointer())
            stem = Builder->CreateLoad(stem->getType()->getPointerTo(), stem, "defer");
        args.push_back(stem);
        dataTypes.push_back(stemSymbol->getDataType());
    } else if (fsymbol->getThisArgDt() != BuildTypes::undefinedType) {
        // calling a function of the type itself, without stem
        Type *thisTy = buildTypes->llvmType(func->getThisArgDt());
        Value *ptr = Builder->CreateLoad(thisTy->getPointerTo(), func->getThisArg(), "derefthis");
        args.push_back(ptr);
        dataTypes.push_back(fsymbol->getThisArgDt());
    }

    ArrayRef<Value*> argsRef(args);

    Builder->SetInsertPoint(allocblock);
    Value *vfunc = symbol->getLLVMValue(func);
    if (!vfunc) {
        return NULL; //FIXME:??
    }
    Function *cfunc = dyn_cast<Function>(vfunc);

    // symbol->getLLVMValue above can emit another location (preGenerate of the 
    // function being called), so we emit location again
    RobDbgInfo.emitLocation(this);

    // calling an interface function; will use the dispatcher
    if (stemSymbol && buildTypes->isInterface(stemSymbol->getDataType())) {
        string func_full_name;
        
        func_full_name = buildTypes->name(stemSymbol->getDataType());
        func_full_name.append(":");
        func_full_name.append(ident.getLastName());

        Function *intf_cfunc = mainmodule->getFunction(func_full_name);
        if (!intf_cfunc) {
            intf_cfunc = Function::Create(cfunc->getFunctionType(), Function::ExternalLinkage, 
                codeAddrSpace, func_full_name, mainmodule);
            intf_cfunc->setCallingConv(CallingConv::C);
            intf_cfunc->addFnAttr(Attribute::AlwaysInline);
        }
        cfunc = intf_cfunc;
    }

    Builder->SetInsertPoint(block);
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
