
#include "Dispatch.h"
#include "Identifier.h"
#include "Interface.h"
#include "FunctionImpl.h"
#include "BackLLVM.h"
#include "Scanner.h"

void Dispatch::addDataTypeImplementation(DataType base, DataType impl) {
    set<DataType>& impls = dispatchHash[base];
    impls.insert(impl);
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

                // the first field of arg this is the object type id
                Type *thisTy = buildTypes->llvmType(functionDecl->getThisArgDt());
                Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
                Value *indexList[2] = {zero, zero};
                Type *idType = Type::getInt8Ty(global_context);
                Value *idValue = Builder->CreateLoad(idType, functionDecl->getThisArg(), "typeid");

                SwitchInst *switchi = Builder->CreateSwitch(idValue, NULL, impls.size());

                int caseid = 0;
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
                    if (caseid == 0)
                        switchi->setDefaultDest(implDtBlock);
                    else {
                        ConstantInt *implDtId = ConstantInt::get(Type::getInt8Ty(global_context), implDt, true); // TODO: provide better ids, per baseType
                        switchi->addCase(implDtId, implDtBlock);
                    }
                    caseid++;
                }
			}
		}
    }
}