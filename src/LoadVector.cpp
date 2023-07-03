#include "Header.h"

Value *LoadVector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		auto rsym = search_symbol(ident, allocblock, block);	
		/* TODO */
		if (rsym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.", this);
			return NULL;
		}
		auto sym = rsym->value;

		// sym type can be GlobalVariable or AllocInst
		Type *ty = NULL;
		if (auto *aux = dyn_cast<AllocaInst>(sym))
			ty = aux->getAllocatedType();
		else if (auto *aux = dyn_cast<GlobalVariable>(sym))
			ty = aux->getValueType();

		ArrayType *arrayTy = NULL;
		if (ty->isArrayTy()) {
			arrayTy = (ArrayType*)ty;
		}
		else {
			yyerrorcpp("Symbol " + ident + " is not an array.", this);
			return NULL;
		}

		Value *indice = position->generate(func, block, allocblock);
		if (!indice->getType()->isIntegerTy()){
			yyerrorcpp("Index for loading " + ident + " vector should be of type integer.", this);
			return NULL;
		}

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
		LoadInst *ret = new LoadInst(ptr->getResultElementType(), ptr, ident, false, block);
		return ret;
}

