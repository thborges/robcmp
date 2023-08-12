
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

	Value *alloc = NULL;
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *stem = istem.getSymbol(getScope());
		alloc = rsym->getLLVMValue(stem);
		
		if (stem->hasQualifier(qvolatile))
			rsym->setQualifier(qvolatile);
		
		// TODO: When accessing a.x.func(), need to load a and gep x
		//Load loadstem(ident.getStem());
		//loadstem.setParent(this->parent);
		//stem = loadstem.generate(func, block, allocblock);
	} else {
		alloc = rsym->getLLVMValue(func);
	}

	Node *indn = getElementIndex(rsym);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice || !indice->getType()->isIntegerTy()){
		yyerrorcpp("Index to access " + ident.getFullName() + " elements must be of type integer.", this);
		return NULL;
	}

	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value* indexList[2] = {zero, indice};
	GetElementPtrInst* ptr = GetElementPtrInst::Create(rsym->getLLVMType(), alloc, ArrayRef<Value*>(indexList), "", block);
	LoadInst *ret = new LoadInst(ptr->getResultElementType(), ptr, ident.getFullName(), false, block);
	return ret;
}

