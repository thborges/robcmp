
#include "Array.h"
#include "LoadArray.h"
#include "BuildTypes.h"
#include "FunctionImpl.h"

LoadArray::LoadArray(const string &i, Node *pos, location_t loc): BaseArrayOper(i, pos, NULL, loc) {
	addChild(pos);
}

DataType LoadArray::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		Node *symbol = ident.getSymbol(getScope());
		if (symbol) {
			if (getDimensions() == 1 && !buildTypes->isArray(symbol->getDataType())) {
				yyerrorcpp("Symbol " + ident.getFullName() + " is not an array.", this);
				setSemanticError();
			} else if (getDimensions() == 2 && !buildTypes->isMatrix(symbol->getDataType())) {
				yyerrorcpp("Symbol " + ident.getFullName() + " is not a matrix.", this);
				setSemanticError();
			} else
				dt = buildTypes->getArrayElementType(symbol->getDataType());
		} else			
			setSemanticError();
	}
	return dt;
}

Value *LoadArray::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	Node *symbol = ident.getSymbol(getScope());
	if (!symbol)
		return NULL;

	if (!buildTypes->isArrayOrMatrix(symbol->getDataType()))
		return NULL;

	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);

	Value *alloc = NULL;
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *stem = istem.getSymbol(getScope());
		alloc = symbol->getLLVMValue(stem);
		
		if (stem->hasQualifier(qvolatile))
			symbol->setQualifier(qvolatile);
		
		// TODO: When accessing a.x.func(), need to load a and gep x
		//Load loadstem(ident.getStem());
		//loadstem.setParent(this->parent);
		//stem = loadstem.generate(func, block, allocblock);
	} else {
		alloc = symbol->getLLVMValue(func);
	}

	if (!alloc) {
		// this is a compiler error
		yyerrorcpp("Missing the array reference to gep.", this);
		return NULL;
	}

	Node *indn = getElementIndex(symbol);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice || !indice->getType()->isIntegerTy()) { //TODO: replace by isIntegerDataType
		yyerrorcpp("Index to access " + ident.getFullName() + " elements must be of type integer.", this);
		return NULL;
	}

	if (symbol->isPointerToPointer()) {
		Type *ty = buildTypes->llvmType(symbol->getDataType())->getPointerTo();	
		alloc = Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), "deref");
	}

	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value *indexList[2] = {zero, indice};
	Value *ptr = Builder->CreateGEP(symbol->getLLVMType(), alloc, ArrayRef<Value*>(indexList), "gep");
	DataType elementDt = buildTypes->getArrayElementType(symbol->getDataType());
	Type *elemType = buildTypes->llvmType(elementDt);
	LoadInst *ret = Builder->CreateLoad(elemType, ptr, ident.getFullName());

	return ret;
}

Node* BaseArrayOper::getElementIndex(Node *symbol) {
	
	// Get element
	int rows = -1;
	if (const Array *arr = dynamic_cast<const Array*>(symbol))
		rows = arr->getSize();

	return Array::getElementIndex(position, NULL, ident.getFullName(), rows);
}
