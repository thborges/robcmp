#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value
		Value *exprv = expr->generate(func, block, allocblock);

		Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
		Type* I = exprv->getType();
		//Type* I = IntegerType::getInt32Ty(getContext());
		ArrayType* arrayType = ArrayType::get(I, size);
		
		Value* emptyVec = UndefValue::get(arrayType);
		AllocaInst* variable = new AllocaInst(I, 0, name, allocblock);

//		StoreInst *ret = new StoreInst(emptyVec, variable, block);

//		Value* indexList[2] = {ConstantInt::get(exprv->getType(), 0), exprv};
		//		GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, emptyVec, ArrayRef<Value*>(indexList, 2), name, allocblock);
		//Constant* element = Constant::getIntegerValue(I, APInt(32,0));
		//Constant* index0 = Constant::getIntegerValue(I, APInt(32,0));
		//InsertElementInst* insert1 = InsertElementInst(Vec, Elem, Ind, Name, Bloc);
		//InsertElementInst insert1 = llvm::InsertElementInst(emptyVec, element, index0, name, allocblock);

		//AllocaInst* variable = new AllocaInst(emptyVec, 0, name, allocblock);
		//InsertElementInst* variable = new InsertElementInst(emptyVec, element, index0, name, allocblock);
//		InsertValueInst* variable = new InsertValueInst(emptyVec, element, index0, name, allocblock);
		//AllocaInst* variable = new (emptyVec, element, index0, name, allocblock);
		//AllocaInst(arrayType, 0, name, allocblock);

		tabelasym[allocblock][name] = variable;
		return variable;
		// Add to table of symbols
	}
