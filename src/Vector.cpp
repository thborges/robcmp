#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value
		Value *exprv = expr->generate(func, block, allocblock);

		Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
		Type* I = exprv->getType();
		ArrayType* arrayType = ArrayType::get(I, size);
		
		AllocaInst* variable = new AllocaInst(arrayType, 0, name, block);
		tabelasym[allocblock][name] = variable;

//		StoreInst *ret = new StoreInst(emptyVec, variable, block);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		Value *um = ConstantInt::get(Type::getInt8Ty(global_context), 1);

		Value* indexList[2] = {zero, zero};
		GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
		StoreInst *ret = new StoreInst(exprv, gep, false, block);

		Value* indexList2[2] = {zero, um};
		GetElementPtrInst* gep2 = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList2), "", block);
		StoreInst *ret2 = new StoreInst(exprv, gep2, false, block);

		return NULL;

		//Constant* element = Constant::getIntegerValue(I, APInt(32,0));
		//Constant* index0 = Constant::getIntegerValue(I, APInt(32,0));
		//InsertElementInst* insert1 = InsertElementInst(Vec, Elem, Ind, Name, Bloc);
		//InsertElementInst insert1 = llvm::InsertElementInst(emptyVec, element, index0, name, allocblock);

		//AllocaInst* variable = new AllocaInst(emptyVec, 0, name, allocblock);
		//InsertElementInst* variable = new InsertElementInst(emptyVec, element, index0, name, allocblock);
//		InsertValueInst* variable = new InsertValueInst(emptyVec, element, index0, name, allocblock);
		//AllocaInst* variable = new (emptyVec, element, index0, name, allocblock);
		//AllocaInst(arrayType, 0, name, allocblock);

	}
