
#include "LoadArray.h"
#include "Array.h"
#include "BuildTypes.h"
#include "FunctionImpl.h"

LoadArray::LoadArray(const char *i, Node *pos): ident(i), position(pos) {
	addChild(pos);
}

DataType LoadArray::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		Node *symbol = ident.getSymbol(getScope());

		// temporary fallback while matrix is not modified/fixed
		if (!symbol || !buildTypes->isArray(symbol->getDataType())) {
			rsym = dynamic_cast<LinearDataStructure*>(ident.getSymbol(getScope()));
			dt = rsym->getElementDt();
		} else
			dt = buildTypes->getArrayElementType(symbol->getDataType());
	}
	return dt;
}

Value *LoadArray::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	bool localrsym = false;

	if (!rsym) {
		Node *symbol = ident.getSymbol(getScope());
		rsym = dynamic_cast<LinearDataStructure*>(symbol);
		if (!rsym) {
			// when the array has been assigned to another var
			if (buildTypes->isArray(symbol->getDataType())) {
				localrsym = true;
				rsym = new ParamArray(ident.getFullName(), symbol->getDataType());
				rsym->setAlloca(symbol->getLLVMValue(NULL));
				rsym->setPointerToPointer(symbol->isPointerToPointer());
			}
		}
	}
	if (rsym == NULL) {
		yyerrorcpp("Variable " + ident.getFullName() + " not defined or not an array/matrix.", this);
		return NULL;
	}

	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);

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

	if (!alloc) {
		yyerrorcpp("Missing the array reference to gep.", this);
		return NULL;
	}

	Node *indn = getElementIndex(rsym);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice || !indice->getType()->isIntegerTy()){
		yyerrorcpp("Index to access " + ident.getFullName() + " elements must be of type integer.", this);
		return NULL;
	}

	if (rsym->isPointerToPointer()) {
		Type *ty = buildTypes->llvmType(rsym->getDataType())->getPointerTo();	
		alloc = Builder->CreateLoad(ty, alloc, rsym->hasQualifier(qvolatile), "deref");
	}

	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value *indexList[2] = {zero, indice};
	Value *ptr = Builder->CreateGEP(rsym->getLLVMType(), alloc, ArrayRef<Value*>(indexList), "gep");
	Type *elemType = buildTypes->llvmType(rsym->getElementDt());
	LoadInst *ret = Builder->CreateLoad(elemType, ptr, ident.getFullName());

	if (localrsym)
		delete rsym;

	return ret;
}
