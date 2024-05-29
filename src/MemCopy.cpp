
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

    // Get src value
    Value *exprv = expr->generate(func, block, allocblock);
    Type *exprvty = exprv->getType();
    dt = expr->getDataType();

    // Compute the size of src
    const DataLayout &dl = mainmodule->getDataLayout();
    Value *size;
    Value *nelem = NULL;

    if (buildTypes->isArray(dt)) {
        // Load the array size and compute the bytes to copy
        DataType eldt = buildTypes->getArrayElementType(dt);
        TypeSize eltsize = dl.getTypeAllocSize(buildTypes->llvmType(eldt));
        ConstantInt *elbytes = ConstantInt::get(Type::getInt32Ty(global_context), eltsize);
        Load ld("size");
        ld.setScope(expr);
        nelem = ld.generate(func, allocblock, allocblock);
        Builder->SetInsertPoint(allocblock);
        size = Builder->CreateBinOp(Instruction::Mul, elbytes, nelem, "arrsize");
    } else if (buildTypes->isMatrix(dt)) {
        // Load the matrix size and compute the bytes to copy
        DataType eldt = buildTypes->getArrayElementType(dt);
        TypeSize eltsize = dl.getTypeAllocSize(buildTypes->llvmType(eldt));
        ConstantInt *elbytes = ConstantInt::get(Type::getInt32Ty(global_context), eltsize);
        Load ldrows("rows");
        ldrows.setScope(expr);
        Load ldcols("cols");
        ldcols.setScope(expr);
        Builder->SetInsertPoint(allocblock);
        Value *nrows = ldrows.generate(func, allocblock, allocblock);
        Value *ncols = ldcols.generate(func, allocblock, allocblock);
        nelem = Builder->CreateBinOp(Instruction::Mul, nrows, ncols, "matrixelem");
        size = Builder->CreateBinOp(Instruction::Mul, elbytes, nelem, "matrixsize");
    } else {
        TypeSize ts = dl.getTypeAllocSize(buildTypes->llvmType(dt));
        size = ConstantInt::get(Type::getInt32Ty(global_context), ts);
    }

    // Prepare dest memory
    Type *leftvty;
    Value *dest = leftValue->getLLVMValue(func);
    if (dest) {
        leftvty = dest->getType();
        //FIXME: must check the alloc size for array and matrix
    } else {
        Builder->SetInsertPoint(allocblock);
        if (buildTypes->isArrayOrMatrix(dt)) {
            DataType eldt = buildTypes->getArrayElementType(dt);
            dest = Builder->CreateAlloca(buildTypes->llvmType(eldt), dataAddrSpace, nelem, leftValue->getName());
            leftvty = buildTypes->llvmType(dt)->getPointerTo();
        } else {
            leftvty = buildTypes->llvmType(dt);
            dest = Builder->CreateAlloca(buildTypes->llvmType(dt), dataAddrSpace, nelem, leftValue->getName());
        }
        
        leftValue->setAlloca(dest);
        leftValue->setDataType(dt);

        //FIXME: only work for constant symbols
        leftValue->symbols = expr->getSymbols();

        if (debug_info)
            RobDbgInfo.declareVar(this, dest, allocblock);
    }

    if (!dest || !expr || !leftvty->isPointerTy() || 
        !exprvty->isPointerTy()) {
        yyerrorcpp("Can not copy these operands.", this);
        return NULL;
    }

    Builder->SetInsertPoint(block);    
    Builder->CreateMemCpy(dest, Align(1), exprv, Align(1), size);

    return NULL;
}
