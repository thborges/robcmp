
#include "MemCopy.h"
#include "Load.h"
#include "BackLLVM.h"
#include "FunctionImpl.h"

void MemCopy::setLeftValue(Variable *symbol) {
    leftValue = symbol;
}

Value* MemCopy::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    
    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);

    Value *exprv = expr->generate(func, block, allocblock);
    dt = expr->getDataType();
    Type *exprvty = exprv->getType();

    Type *leftvty;
    Builder->SetInsertPoint(allocblock);
    Value *dest = leftValue->getLLVMValue(func);
    if (dest) {
        leftvty = dest->getType();
    } else {
        leftvty = buildTypes->llvmType(dt);
        dest = Builder->CreateAlloca(leftvty, dataAddrSpace, nullptr, leftValue->getName());
        leftValue->setAlloca(dest);
        leftValue->setDataType(dt);
        if (debug_info)
            RobDbgInfo.declareVar(this, dest, allocblock);
    }

    if (!dest || !expr || !leftvty->isPointerTy() || 
        !exprvty->isPointerTy()) {
        yyerrorcpp("Can not copy these operands.", this);
        return NULL;
    }

    Value *srcalloc = Builder->CreateAlloca(exprvty, dataAddrSpace, nullptr, "src");

    Builder->SetInsertPoint(block);
    Value *src = Builder->CreateStore(exprv, srcalloc);

    const DataLayout &dl = mainmodule->getDataLayout();
    Value *size = ConstantInt::get(Type::getInt32Ty(global_context), dl.getTypeAllocSize(leftvty));

    Builder->CreateMemCpy(dest, Align(1), srcalloc, Align(1), size);

    return NULL;
}
