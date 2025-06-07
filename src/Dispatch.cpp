
#include "Dispatch.h"
#include "Identifier.h"
#include "Interface.h"
#include "FunctionImpl.h"
#include "BackLLVM.h"
#include "Program.h"
#include "UserType.h"
#include "Scanner.h"

void Dispatch::addDataTypeImplementation(DataType base, DataType impl) {
    //errs() << "addDataTypeImplementation: " << buildTypes->name(base) << " -> " << buildTypes->name(impl) << "\n";
    set<DataType>& impls = dispatchHash[base];
    impls.insert(impl);
}

int Dispatch::getImplementationCount(DataType intf) {
    if (dispatchHash.find(intf) != dispatchHash.end())
        return dispatchHash[intf].size();
    return 0;
}

void Dispatch::addIntfInvocation(DataType intf) {
    intfsInvoked.insert(intf);
}

void Dispatch::generateDispatchFunctions(Node *scope) {

    /* for each base type, generates a function:
        void base_type.method(this) {
            switch (this.id) {
                case x: xtype->method(this);
                case y: ytype->method(this);
                ...
            }
        }
    */

    for(auto& [baseType, impls] : dispatchHash) {
        string baseTypeName = buildTypes->name(baseType);
        Identifier baseTypeId(baseTypeName, scope->getLoc());
        Node *baseTypeNode = baseTypeId.getSymbol(scope);
        Interface *baseTypeTy = dynamic_cast<Interface*>(baseTypeNode);

	    for(const auto & [method, function] : baseTypeTy->getSymbols()) {
			if (FunctionDecl *functionDecl = dynamic_cast<FunctionDecl*>(function)) {

                // if the function is declared in this module, FunctionCall already create it
                string dispatchFuncName = baseTypeName + ":" + method;
                Function *dispatchFunc = mainmodule->getFunction(dispatchFuncName);
                if (!dispatchFunc) {
                    dispatchFunc = Function::Create(functionDecl->getLLVMFunction()->getFunctionType(), 
                        Function::ExternalLinkage, codeAddrSpace, dispatchFuncName, mainmodule);
                    dispatchFunc->setCallingConv(CallingConv::C);
                    if (impls.size() == 1)
                        dispatchFunc->addFnAttr(Attribute::AlwaysInline);
                }

                auto fblock = BasicBlock::Create(global_context, "", dispatchFunc);
                Builder->SetInsertPoint(fblock);

                if (impls.size() == 0) {
                    // provide an empty implementation for the dispatcher
                                        
                    Type *retTy = dispatchFunc->getReturnType();
                    if (retTy->isVoidTy()) {
                        Builder->CreateRetVoid();
                    } else {
                        // this returns zero for integers and floats
                        Builder->CreateRet(Constant::getNullValue(retTy));
                    }
                    continue;
                }

                // the first field of arg this is the object type id
                Type *thisTy = buildTypes->llvmType(functionDecl->getThisArgDt());
                Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
                Value *indexList[2] = {zero, zero};
                Type *idType = Type::getInt8Ty(global_context);
                Value *idValue = Builder->CreateLoad(idType, functionDecl->getThisArg(), "typeid");

                SwitchInst *switchi = Builder->CreateSwitch(idValue, NULL, impls.size());

                bool hasDefault = false;
                for(DataType implDt : impls) {
                    auto implDtBlock = BasicBlock::Create(global_context, "", dispatchFunc);
                    Builder->SetInsertPoint(implDtBlock);

					vector<Value*> args;
					for(auto& arg : dispatchFunc->args()) {
						args.push_back(&arg);
					}
					
                    string destTypeName = buildTypes->name(implDt);
                    string destFuncName = destTypeName + ":" + method;
                    Function *destFunc = mainmodule->getFunction(destFuncName);

                    if (!destFunc) {
                        yyerrorcpp(string_format("Function %s not found while generating dispatch.", 
                            destFuncName.c_str()), scope);
                        continue;
                    }

					Value *call = Builder->CreateCall(destFunc, args);
					if (call->getType()->isVoidTy())
						Builder->CreateRetVoid();
					else
						Builder->CreateRet(call);

                    // add switch case
                    Builder->SetInsertPoint(fblock);
                    if (!hasDefault && destTypeName.find("void_") == string::npos) {
                        //TODO: The default should halt the MCU? For security reasons, memory corruption, control flow hijack.
                        switchi->setDefaultDest(implDtBlock);
                        hasDefault = true;
                    } else {
                        UserType *type = dynamic_cast<UserType*>(program->findSymbol(destTypeName));
                        assert(type && "UserType should exists.");
                        int concreteId = type->getConcreteId();
                        if (concreteId != -1) {
                            ConstantInt *implDtId = ConstantInt::get(Type::getInt8Ty(global_context), concreteId, true);
                            switchi->addCase(implDtId, implDtBlock);
                        }
                    }
                }
			}
		}
    }
}

void Dispatch::notifyInterface(DataType intf) {
    dispatchHash[intf];
}

bool Dispatch::isIntfInvoked(DataType intf) {
    return (intfsInvoked.find(intf) != intfsInvoked.end());
}