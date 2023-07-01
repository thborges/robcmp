#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		//Create a Vector of Type Int8, and Size = size.
		size = elements->getArraySize();
		Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
		
		//Get Type of elements in Vector of Elements, and define as I.
		Type* I = elements->getArrayType();

		//Declare array type.
		ArrayType* arrayType = ArrayType::get(I, size);
		
		//Allocate vector.
		Value* variable;
		if (allocblock == global_alloc) { // when alloc is on main, global
			GlobalVariable *gv = new GlobalVariable(*mainmodule, arrayType, 
				false, GlobalValue::ExternalLinkage, NULL, name);
			ConstantAggregateZero* const_array = ConstantAggregateZero::get(arrayType);
			gv->setInitializer(const_array);
			variable = gv;
		} else {
			variable = new AllocaInst(arrayType, 0, name, allocblock);
		}

		//Add vector to table of symbols.
		tabelasym[allocblock][name] = new RobSymbol(variable);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		StoreInst *store = NULL;
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
				store = new StoreInst(val, gep, false, block);
			}
		}
		

		return store;
	}
