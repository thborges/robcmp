#include "Header.h"

	Value *Matrix::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value

		//Create a Vector of Type Int8, and Size = size.
		size_l = arrays->getLineSize();
		size_c = arrays->getColumnSize();
		Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size_l);
		
		//Get Type of elements in Vector of Elements, and define as I.
		Type* I = arrays->getMatrixType(func, block, allocblock);

		//Declare matrix type.
		ArrayType* arrayType = ArrayType::get(I, size_l);
		ArrayType* matrixType = ArrayType::get(arrayType, size_c);
		
		//Allocate matrix.
		AllocaInst* variable = new AllocaInst(matrixType, 0, name, block);
		
		//Add matrix to table of symbols.
		tabelasym[allocblock][name] = variable;

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		unsigned int index = 0;
		for(auto& i: arrays->elements)
		{
			unsigned elCount = i.count;
			for (int j=0; j<elCount; j++)
			{
				for(auto& k: i.array->elements)
				{
					unsigned elCountl = k.count;
					for (int l=0; l<elCountl; l++)
					{
						Node* elValue = k.value;
				
						Value *val = elValue->generate(func, block, allocblock);//ConstantInt::get(Type::getInt16Ty(global_context), 2);//elValue->generate(func, block, allocblock);
						val = Coercion::Convert(val, I, block);
		
						Value *idx = ConstantInt::get(Type::getInt8Ty(global_context), index);
						//index++;

						Value* indexList[2] = {zero, idx};
						GetElementPtrInst* gep = GetElementPtrInst::CreateInBounds(matrixType, variable, ArrayRef<Value*>(indexList), "", block);
						GetElementPtrInst* gop = GetElementPtrInst::CreateInBounds(arrayType, gep, ArrayRef<Value*>(indexList), "", block);
						StoreInst *store = new StoreInst(val, gop, false, block);
						//GetElementPtrInst* ngep = GetElementPtrInst::Create(arrayType, variable, ArrayRef<Value*>(indexList), "", block);
						//LoadInst *ret = new LoadInst(arrayType, 0, name, allocblock);
					}
				}
			}
		}
		

		return NULL;
	}
