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
		Value* variable;
		if (allocblock == global_alloc) { // when alloc is on main, global
			GlobalVariable *gv = new GlobalVariable(*mainmodule, matrixType, 
				false, GlobalValue::ExternalLinkage, NULL, name);
			ConstantAggregateZero* const_array = ConstantAggregateZero::get(matrixType);
			gv->setInitializer(const_array);
			variable = gv;
		} else {
			variable = new AllocaInst(matrixType, 0, name, allocblock);
		}
		
		//Add matrix to table of symbols.
		tabelasym[allocblock][name] = variable;

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		// {{1:3}:3, {1:2,2}:2}
		// {{1,1,1},{1,1,1},{1,1,1},
		//  {1,1,2},{1,1,2}
		int idxline = -1;
		for(auto& i: arrays->elements)
		{
			unsigned elCount = i.count;
			for (int j=0; j<elCount; j++)
			{
				idxline++;
				Value *vidxline = ConstantInt::get(Type::getInt8Ty(global_context), idxline);
				Value* linelist[2] = {zero, vidxline};
				GetElementPtrInst* gep = GetElementPtrInst::CreateInBounds(matrixType, 
					variable, ArrayRef<Value*>(linelist), "gepline", block);

				int idxcol = -1;
				for(auto& k: i.array->elements)
				{
					Node* elValue = k.value;
					Value *val = elValue->generate(func, block, allocblock);
					val = Coercion::Convert(val, I, block);

					unsigned elCountl = k.count;
					for (int l=0; l<elCountl; l++)
					{
						idxcol++;
						Value *vidxcol = ConstantInt::get(Type::getInt8Ty(global_context), idxcol);
						Value* collist[2] = {zero, vidxcol};
		
						GetElementPtrInst* gop = GetElementPtrInst::CreateInBounds(arrayType, 
							gep, ArrayRef<Value*>(collist), "gepcol", block);
						StoreInst *store = new StoreInst(val, gop, false, block);
					}
				}
			}
		}
		

		return NULL;
	}
