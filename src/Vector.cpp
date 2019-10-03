#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value
		//CHANGE: Load Vector of elements.
		Value *exprv = expr->generate(func, block, allocblock);

		//TO-DO: define size as number of elements in vector of elements.

		//Create a Vector of Type Int8, and Size = size.
		//size = elements.size()
		Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
		
		//Get Type of elements in Vector of Elements, and define as I.
		Type* I = exprv->getType();

		//Declare array type.
		ArrayType* arrayType = ArrayType::get(I, size);
		
		//Allocate vector.
		AllocaInst* variable = new AllocaInst(arrayType, 0, name, block);
		
		//Add vector to table of symbols.
		tabelasym[allocblock][name] = variable;

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		for (int i=0; i<size; i++)
		{
			Value *um = ConstantInt::get(Type::getInt8Ty(global_context), i);
			Value* indexList[2] = {zero, um};
			GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
			//TO-DO: Get element on position X on vector elements.
			StoreInst *store = new StoreInst(exprv, gep, false, block);
			//GetElementPtrInst* ngep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
			LoadInst *ret = new LoadInst(arrayType, 0, name, allocblock);
		}
		

		return NULL;
	}
