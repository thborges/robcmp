#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value

		//Create a Vector of Type Int8, and Size = size.
		size = elements->getArraySize();
		Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
		
		//Get Type of elements in Vector of Elements, and define as I.
		Type* I = elements->getArrayType(func, block, allocblock);

		//Declare array type.
		ArrayType* arrayType = ArrayType::get(I, size);
		
		//Allocate vector.
		AllocaInst* variable = new AllocaInst(arrayType, 0, name, block);
		
		//Add vector to table of symbols.
		tabelasym[allocblock][name] = variable;

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		unsigned int struct_size = elements->getStructSize();
		unsigned int index = 0;
		for (int i=0; i<struct_size; i++)
		{
			unsigned elCount = elements->getElementCount(i);
			for (int j=0; j<elCount; j++)
			{
				Node* elValue = elements->getStructElement(i);
				Value *val = elValue->generate(func, block, allocblock);
				val = Coercion::Convert(val, I, block);

				Value *idx = ConstantInt::get(Type::getInt8Ty(global_context), index);
				index++;

				Value* indexList[2] = {zero, idx};
				GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
				StoreInst *store = new StoreInst(val, gep, false, block);
				//GetElementPtrInst* ngep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
				//LoadInst *ret = new LoadInst(arrayType, 0, name, allocblock);
			}
		}
		

		return NULL;
	}
