#include "Header.h"

Type* LoadArray::getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) {
	if (!rsym)
		rsym = search_symbol(ident, allocblock, block);
	if (rsym) {
		Type *ty = NULL;
		if (auto *aux = dyn_cast<AllocaInst>(rsym->value))
			ty = aux->getAllocatedType();
		else if (auto *aux = dyn_cast<GlobalVariable>(rsym->value))
			ty = aux->getValueType();
		
		if (ty->isArrayTy()) {
			ArrayType *arrayTy = (ArrayType*)ty;
			return arrayTy->getArrayElementType();
		}
	}
	return NULL;
}

Value *LoadArray::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	rsym = search_symbol(ident, allocblock, block);	
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

	Node *indn = getLoadIndex(rsym, block, allocblock);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice->getType()->isIntegerTy()){
		yyerrorcpp("Index to update " + ident + " elements should be of type integer.", this);
		return NULL;
	}

	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value* indexList[2] = {zero, indice};
	GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
	LoadInst *ret = new LoadInst(ptr->getResultElementType(), ptr, ident, false, block);
	return ret;
}

