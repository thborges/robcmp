#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value

		//TO-DO: define size as number of elements in vector of elements.

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
		for (int i=0; i<struct_size; i++)
		{
			unsigned elCount = elements->getElementCount(i);
			for (int j=0; j<elCount; j++)
			{
				Node* elValue = elements->getStructElement(i);
				Value *index = elValue->generate(func, block, allocblock);
//ConstantInt::get(Type::getInt8Ty(global_context), j);//elValue->generate(func, block, allocblock);
				Value* indexList[2] = {zero, index};
				GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
				StoreInst *store = new StoreInst(index, gep, false, block);
				//GetElementPtrInst* ngep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
				//LoadInst *ret = new LoadInst(arrayType, 0, name, allocblock);
			}
		}
		

		return NULL;
	}
