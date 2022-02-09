#include "Header.h"

Value *UpdateVector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		/* TODO */
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}

		// sym type can be GlobalVariable or AllocInst
		Type *ty = sym->getType();
		if (ty->isPointerTy()) // global variable is always pointer
			ty = ((PointerType*)ty)->getElementType();
	
		ArrayType *arrayTy = NULL;
		if (ty->isArrayTy()) {
			arrayTy = (ArrayType*)ty;
		}
		else {
			yyerrorcpp("Symbol " + ident + " is not of array type.");
			return NULL;
		}

		Value *indice = position->generate(func, block, allocblock);
		if (!indice->getType()->isIntegerTy()){
			yyerrorcpp("Index to update " + ident + " vector should be of integer type.");
			return NULL;
		}

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
		Value *val = exprs->generate(func, block, allocblock);
		StoreInst *store = new StoreInst(val, ptr, false, block);

		return store;
}

