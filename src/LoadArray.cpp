
#include "LoadArray.h"
#include "Array.h"
#include "FunctionImpl.h"

LoadArray::LoadArray(const char *i, Node *pos): ident(i), position(pos) {
	addChild(pos);
}

DataType LoadArray::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		if (!rsym)
			rsym = dynamic_cast<LinearDataStructure*>(ident.getSymbol(getScope()));
		if (rsym)
			dt = rsym->getElementDt();
	}
	return dt;
}

Value *LoadArray::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	if (!rsym)
		rsym = dynamic_cast<LinearDataStructure*>(ident.getSymbol(getScope()));
	if (rsym == NULL) {
		yyerrorcpp("Variable " + ident.getFullName() + " not defined or not an array/matrix.", this);
		return NULL;
	}
	auto sym = rsym->getLLVMValue(func);

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
		yyerrorcpp("LLVM Symbol " + ident.getFullName() + " is not an array.", this);
		return NULL;
	}

	Node *indn = getElementIndex(rsym);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice || !indice->getType()->isIntegerTy()){
		yyerrorcpp("Index to access " + ident.getFullName() + " elements must be of type integer.", this);
		return NULL;
	}

	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value* indexList[2] = {zero, indice};
	GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
	LoadInst *ret = new LoadInst(ptr->getResultElementType(), ptr, ident.getFullName(), false, block);
	return ret;
}

