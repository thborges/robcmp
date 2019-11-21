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
	//	ArrayType *matrixTy = dyn_cast<ArrayType>(arrayTy->classof(Type::getArrayElementType()));
		if (arrayTy == NULL) {
			yyerrorcpp("Matrix " + ident + " is not an array type.");
			return NULL;
		}
		Value *indice = position_1->generate(func, block, allocblock);
		if (!indice->getType()->isIntegerTy()){
			yyerrorcpp("Not Allowed");
			return NULL;
		}

		Value *indice_2 = position_2->generate(func, block, allocblock);

		if (!indice_2->getType()->isIntegerTy()){
			yyerrorcpp("Not Allowed");
			return NULL;
		}

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
//		Value *indice = ConstantInt::get(Type::getInt8Ty(global_context), position_1);

		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::CreateInBounds(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);

	//	Value* indexList2[2] = {zero, indice_2};
	//	GetElementPtrInst* gep = GetElementPtrInst::Create(arrayTy, ptr, ArrayRef<Value*>(indexList2), "", block);
		LoadInst *ret = new LoadInst(ptr, ident, false, block);

		return ret;
	//	return ret;
}

