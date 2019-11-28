#include "Header.h"

Value *LoadMatrix::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		/* TODO */
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}
		
		AllocaInst *allocInst = dyn_cast<AllocaInst>(sym);
		ArrayType *arrayTy = dyn_cast<ArrayType>(allocInst->getAllocatedType());
		//ArrayType *matrixTy = dyn_cast<ArrayType *>(arrayTy->classOf());
		if (arrayTy == NULL) {
			yyerrorcpp("Matrix " + ident + " is not an array type.");
			return NULL;
		}
		
		//Generate first param.
		Value *indice = position_1->generate(func, block, allocblock);
		if (!indice->getType()->isIntegerTy()){
			yyerrorcpp("Not Allowed");
			return NULL;
		}

		//Generate second param.
		Value *indice_2 = position_2->generate(func, block, allocblock);
		if (!indice_2->getType()->isIntegerTy()){
			yyerrorcpp("Not Allowed");
			return NULL;
		}

		//Get Vector in Matrix
		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::CreateInBounds(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
//		LoadInst *l = new LoadInst(ptr, ident, false, block);

		//Get Element in Vector
		Value* indexList2[2] = {zero, indice_2};
		//GetElementPtrInst* gep = GetElementPtrInst::Create(matrixTy, ptr, ArrayRef<Value*>(indexList2), "", block);
		LoadInst *ret = new LoadInst(ptr, ident, false, block);

		return ret;
	//	return ret;
}

