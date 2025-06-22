
#include "ConstructorCall.h"
#include "BackLLVM.h"
#include "Program.h"
#include "UserType.h"

Value* ConstructorCall::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

    if (dt == BuildTypes::undefinedType)
        getDataType();
    
    // alloc
    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);
    GlobalVariable *gv = NULL;

    Value *var;
    if (leftGEP) {
        // init a previously set gep (e.g., array element)
        var = leftGEP;
    } else {
        assert(leftValue && "leftValue or gep must be set.");
        var = leftValue->getLLVMValue(func);
    }
    
    if (var == NULL) {
        // is a new left var
        Type *vty = buildTypes->llvmType(dt);
        if (buildTypes->isInterface(dt)) {
            vty = PointerType::getUnqual(vty);
            leftValue->setPointerToPointer(true);
        }
        Builder->SetInsertPoint(allocblock);
        if (allocblock == global_alloc) {
            //Constant *init = ConstantAggregateZero::get(buildTypes->llvmType(dt));
            PointerType *dtPointerTy = PointerType::getUnqual(buildTypes->llvmType(dt));
            Constant *init = ConstantPointerNull::get(dtPointerTy);
            gv = new GlobalVariable(*mainmodule, vty, hasQualifier(qconst), 
                GlobalValue::ExternalLinkage, init, leftValue->getName());
            var = gv;
        } else {
            var = Builder->CreateAlloca(vty, dataAddrSpace, 0, 
                leftValue->getName());
        }
        leftValue->setAlloca(var);
        leftValue->setDataType(dt);
        if (debug_info) {
            if (allocblock != global_alloc)
                RobDbgInfo.declareVar(leftValue, var, allocblock);
        }
    }
    vector<Value*> args;
    args.push_back(var);
    
    // if calling a constructor of an interface, emit code to bind it
    if (buildTypes->isInterface(dt)) {
        Node *scope = leftValue->getScope();
        UserType *parent= dynamic_cast<UserType*>(scope);
        const string toInjection = parent ?
            parent->getName() + "." + leftValue->getName() :
            leftValue->getName();

        const string injectFuncName = "__get_injection_for_" + toInjection;
        Node *funcNode = findSymbol(injectFuncName);
        FunctionBase *funcDecl = dynamic_cast<FunctionBase*>(funcNode);
        if (!funcDecl) {
            funcDecl = new FunctionDecl(dt, injectFuncName, new FunctionParams(), this->getLoc());
            funcDecl->setReturnIsPointer(true);
            funcDecl->setScope(program);
            funcDecl->setLocation(this);
            funcDecl->generate(NULL, NULL, global_alloc);
            funcDecl->setAttributes(new FunctionAttributes(fa_inline));
            program->addSymbol(funcDecl);
        }
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(allocblock == global_alloc ? global_alloc : block);
        return Builder->CreateCall(funcDecl->getLLVMFunction());

    } else {
        // call the init constructor

        // find the user type
        Node *type = findSymbol(name);
        if (!type)
            return NULL;

        Node *fsymbol = type->findMember("init");
        assert(fsymbol && "the init method for the type must exists");
        
        FunctionBase *initfunc = dynamic_cast<FunctionBase*>(fsymbol);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(allocblock == global_alloc ? global_alloc : block);

        if (initfunc->needsParent()) {
            Type *thisTy = buildTypes->llvmType(func->getThisArgDt());
            Value *ptr = Builder->CreateLoad(PointerType::getUnqual(thisTy), func->getThisArg(), "derefthis");
            args.push_back(ptr);
        }

        CallInst *c = Builder->CreateCall(initfunc->getLLVMFunction(), ArrayRef<Value*>(args));
        return NULL; // init doesn't return; is a call to a void func
    }
}
