
#include "ArrayAccess.h"

Value* ArrayAccess::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    // Force datatype, if not queried yet
    getDataType();
    
    // Load the pointer for the array
    Value *alloc = leftValue->generateNewBlock(func, &block, allocblock);

    // Load the index value
    Value *index = expr->generateNewBlock(func, &block, allocblock);

    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);

    // x[a]
    Type *leftTy = buildTypes->llvmType(dt);
    if (buildTypes->isComplex(dt)) { // an array of refs
        leftTy = PointerType::get(global_context, 0);
        loadSymbol = leftValue->getLoadSymbol();
    }
    ArrayType *arrayTy = ArrayType::get(leftTy, 0);
	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value *indexList[2] = {zero, index}; 
	Value *gep = Builder->CreateGEP(arrayTy, alloc, indexList, "elemgep");
    if (toStore)
        return gep;
    return Builder->CreateLoad(leftTy, gep, "deref");
}

DataType ArrayAccess::getDataType() {
    if (dt == BuildTypes::undefinedType)
        dt = buildTypes->getArrayElementType(leftValue->getDataType());
    return dt;
}
