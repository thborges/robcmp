
#include "MatrixAccess.h"
#include "BinaryOp.h"
#include "semantic/PropagateTypes.h"

Value* MatrixAccess::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    // Force datatype, if not queried yet
    getDataType();
    
    // Load the pointer for the matrix
    Value *alloc = leftValue->generateNewBlock(func, &block, allocblock);

    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);

    // find matrix column number in the context
    Node *cols = NULL;
    Node *rows = NULL;
    loadSymbol = leftValue->getLoadSymbol();
    if (loadSymbol) {
        cols = loadSymbol->findMember("cols");
        rows = loadSymbol->findMember("rows");
    }
    assert(cols && rows && "MatrixAccess needs the load symbol to identify the number of cols/rows");
    Node *loadcols = new Load(cols);
    loadcols->setScope(loadSymbol);

    // the resulting index should be wider to contains (cols * rows) result
    DataType dtcols = cols->getDataType();
    DataType dtrows = rows->getDataType();
    DataType index_needed_dt = max(dtcols, dtrows);
    switch (index_needed_dt) {
        case tint8:
        case tint8u:
            index_needed_dt = tint16u;
            break;
        case tint16:
        case tint16u:
            index_needed_dt = tint32u;
            break;
        default:
            index_needed_dt = tint64u;
            break;    
    }
    Node *expr1_new_dt = PropagateTypes::coerceTo(expr1, index_needed_dt);

    // Compute array index
    BinaryOp *op = new BinaryOp(new BinaryOp(expr1_new_dt, '*', loadcols), '+', expr2);
	PropagateTypes pt;
	pt.visit(*op);
    Value *index = op->generateNewBlock(func, &block, allocblock);
    Builder->SetInsertPoint(block);

    Type *leftTy = buildTypes->llvmType(dt);
    if (buildTypes->isComplex(dt)) // an array of refs
        leftTy = PointerType::getUnqual(leftTy);
    ArrayType *arrayTy = ArrayType::get(leftTy, 0);
	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value *indexList[2] = {zero, index}; 
	Value *gep = Builder->CreateGEP(arrayTy, alloc, indexList, "elemgep");
    if (toStore)
        return gep;
    return Builder->CreateLoad(leftTy, gep, "deref");
}

DataType MatrixAccess::getDataType() {
    if (dt == BuildTypes::undefinedType)
        dt = buildTypes->getArrayElementType(leftValue->getDataType());
    return dt;
}
