#include "FunctionCall.h"
#include "BuildTypes.h"
#include "Cast.h"
#include "FunctionDecl.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "Coercion.h"
#include "Load.h"
#include "Visitor.h"
#include "BackLLVM.h"
#include "UserType.h"
#include "Program.h"

extern Program *program;



DataType FunctionCall::getDataType() {
    
    if (dt == BuildTypes::undefinedType) {
        // is a cast or constructor?
        dt = buildTypes->getType(ident.getFullName());
        if (parameters->getNumParams() <= 1 && dt != BuildTypes::undefinedType) {
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

    // check if it is a cast call: the function name is a primitive type, e.g., int8(x)
    DataType adt = buildTypes->getType(name);
    if (adt != BuildTypes::undefinedType) {
        dt = adt;
        unsigned p = parameters->getNumParams();
        // call with only one parameter is a cast
        if (p == 1) {
            Node *param = parameters->getParamElement(0);
            Cast ca(dt, param);
            ca.setScope(this);
            if (!param->getScope())
                param->setScope(&ca);
            return ca.generate(func, block, allocblock);

        } else if (p == 0) { // it's a constructor			
            // alloc
            Builder->SetInsertPoint(block);
            Value *var = leftValue->getLLVMValue(func);
            if (var == NULL) {
                Builder->SetInsertPoint(allocblock);
                var = Builder->CreateAlloca(buildTypes->llvmType(dt), dataAddrSpace, 0, 
                    leftValue->getName());
                leftValue->setAlloca(var);
                leftValue->setDataType(dt);
                if (debug_info)
                    RobDbgInfo.declareVar(leftValue, var, allocblock);
            }
            vector<Value*> args;
            args.push_back(var);

            // call :init
            Node *type = findSymbol(name);
            if (!type)
                return NULL;
            

            Node *fsymbol = type->findMember("init");
            if (!fsymbol) {
                //extern map<string, vector<pair<string, BindScope>>> injections; 
                // se presente no injection
                // consultar b3, se não criado criar um
                // new Scalar("<nome-variavel>", new FC("b3", new ParamsCall()))
                // return new Load("<nome-variavel>") 
                
                Node *scope = leftValue->getScope();
                UserType *parent= dynamic_cast<UserType*>(scope);

                if (parent == NULL) {
                    return NULL;
                }

                const string toInjection = parent->getName() + "." + leftValue->getName();
                if (injections.count(toInjection) == 0) {
                    return NULL;
                }


                const string variableName = ":injectionName__" + injections[toInjection].first;
                // if (map_injections.count(variableName) == 0) {
                //     Variable *injectionVariable = new Scalar(variableName, new FunctionCall(injections[toInjection].first, new ParamsCall()));
                //     map_injections[variableName] = injectionVariable;

                //     // TODO: Verificar se a função main já foi gerada
                //     // injectionVariable->gene
                //     program->addChild(injectionVariable);
                //     program->addSymbol(injectionVariable);
                // }

                Load ld(variableName);

                ld.setScope(program);

				// change FunctionCall datatype to the datatype of the injected var
				dt = ld.getDataType();
				Node *lsymbol = findSymbol(leftValue->getName());
				lsymbol->setDataType(dt);

                return ld.generate(func, block, allocblock);
            }

            FunctionBase *initfunc = dynamic_cast<FunctionBase*>(fsymbol);
            
            Builder->SetInsertPoint(block);

            if (initfunc->needsParent()) {
                Type *thisTy = buildTypes->llvmType(func->getThisArgDt());
                Value *ptr = Builder->CreateLoad(thisTy->getPointerTo(), func->getThisArg(), "derefthis");
                args.push_back(ptr);
            }

            CallInst *c = Builder->CreateCall(initfunc->getLLVMFunction(), ArrayRef<Value*>(args));
            return NULL;
        }
    }

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
    }

    if (fsymbol->getNumCodedParams() != parameters->getNumParams()) {
        yyerrorcpp(string_format("Function %s has %d argument(s) but was called with %d.",
            name.c_str(), fsymbol->getNumCodedParams(), 
            parameters->getNumParams()), this);
        yywarncpp("The function declaration is here.", symbol);
        return NULL;
    }

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
    for (int i = 0, j = 0; i < parameters->getNumParams(); i++, j++) {
        Node *param = parameters->getParamElement(i);
        DataType call_dt = param->getDataType();
        DataType def_dt = fsymbol->getParameters().getParamType(j);

        Value *valor = param->generate(func, block, allocblock);
        if (!valor)
            return NULL;

        if (buildTypes->isInterface(call_dt)) {
            valor = Builder->CreateLoad(valor->getType()->getPointerTo(), valor, "defer");
        } else if (buildTypes->isComplex(call_dt)) {
            //we don't support cohercion between user types yet
            if (call_dt != def_dt) {
                yyerrorcpp(string_format("Argument %s expects '%s' but '%s' was provided.",
                    fsymbol->getParameters().getParamName(i).c_str(),
                    buildTypes->name(def_dt), 
                    buildTypes->name(call_dt)), this);
                yywarncpp("The function declaration is here.", fsymbol);
            }
        } else if (buildTypes->isArrayOrMatrix(call_dt)) {
            if (call_dt != def_dt) {
                yyerrorcpp(string_format("Argument %s expects '%s' but '%s' was provided.",
                    fsymbol->getParameters().getParamName(i).c_str(),
                    buildTypes->name(def_dt), 
                    buildTypes->name(call_dt)), this);
            }

            // we pass the address of the first element
            Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
            Value *indexList[2] = {zero, zero};
            Value *ptr = Builder->CreateGEP(param->getLLVMType(), valor, ArrayRef<Value*>(indexList), "gep");
            valor = ptr;
        } else {
            Type *pty = buildTypes->llvmType(def_dt);
            valor = Coercion::Convert(valor, pty, block, this);
        }
        args.push_back(valor);

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
                string pname = param->getName() + p;
                Load ld(pname);
                ld.setScope(func);
                valor = ld.generate(func, block, allocblock);
                valor = Coercion::Convert(valor, buildTypes->llvmType(tint32), block, this);
                args.push_back(valor);
                j++;
            }
        }
    }

    // this parameter
    if (stemSymbol) {
        if (stemSymbol->isPointerToPointer())
            stem = Builder->CreateLoad(stem->getType()->getPointerTo(), stem, "defer");
        args.push_back(stem);
    }

    ArrayRef<Value*> argsRef(args);

    Builder->SetInsertPoint(allocblock);
    Value *vfunc = symbol->getLLVMValue(func);
    Function *cfunc = dyn_cast<Function>(vfunc);

    // when calling an interface function, generate a complete name
    // to enable injection at link time (symbol name substitution)
    if (stemSymbol && buildTypes->isInterface(stemSymbol->getDataType())) {
        string inject_name = stemSymbol->getScope()->getName() + ":";
        inject_name.append(stemSymbol->getName() + ":");
        inject_name.append(ident.getLastName());
        Function *intf_cfunc = mainmodule->getFunction(inject_name);
        if (!intf_cfunc) {
            intf_cfunc = Function::Create(cfunc->getFunctionType(), Function::ExternalLinkage, 
                codeAddrSpace, inject_name, mainmodule);
            intf_cfunc->setDSOLocal(true);
            intf_cfunc->setCallingConv(CallingConv::C);
        }
        cfunc = intf_cfunc;
    }

    Builder->SetInsertPoint(block);
    return Builder->CreateCall(cfunc, argsRef);
}

void FunctionCall::accept(Visitor& v) {
    v.visit(*this);
}
