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
		if (arrayTy == NULL) {
			yyerrorcpp("Matrix " + ident + " is not an array type.");
			return NULL;
		}

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		Value *indice = ConstantInt::get(Type::getInt8Ty(global_context), position_1);

		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::CreateInBounds(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
//		GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, sym, ArrayRef<Value*>(indexList), "", block);
		LoadInst *ret = new LoadInst(ptr, ident, false, block);

		return ret;
	//	return ret;
}

