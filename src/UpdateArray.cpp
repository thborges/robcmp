
#include "UpdateArray.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"

UpdateArray::UpdateArray(const string &i, Node *pos, Node *expr, location_t loc): 
	BaseArrayOper(i, pos, NULL, loc) {
	this->expr = expr;
	addChild(pos);
	addChild(expr);
}

DataType UpdateArray::getElementDataType() {
	if (element_dt == BuildTypes::undefinedType) {
		Node *symbol = ident.getSymbol(getScope());
		if (symbol && buildTypes->isArrayOrMatrix(symbol->getDataType()))
			element_dt = buildTypes->getArrayElementType(symbol->getDataType());
	}
	return element_dt;
}

Value *UpdateArray::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	Node *symbol = ident.getSymbol(getScope());
	if (!symbol)
		return NULL;

	if (!buildTypes->isArrayOrMatrix(symbol->getDataType())) {
		yyerrorcpp("Symbol " + ident.getFullName() + " is not an array or matrix.", this);
		return NULL;
	}

	Builder->SetInsertPoint(block);
	Value *sym = symbol->getLLVMValue(func);

	// sym type can be GlobalVariable or AllocInst
	Type *ty = NULL;
	if (auto *aux = dyn_cast<AllocaInst>(sym))
		ty = aux->getAllocatedType();
	else if (auto *aux = dyn_cast<GlobalVariable>(sym))
		ty = aux->getValueType();

	Node *indn = getElementIndex(symbol);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice || !indice->getType()->isIntegerTy()){
		yyerrorcpp("Index to update " + ident.getFullName() + " elements must be of type integer.", this);
		return NULL;
	}

	Value *val = expr->generate(func, block, allocblock);
	ArrayType *arrayTy = (ArrayType*)buildTypes->llvmType(symbol->getDataType());

	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);

	if (symbol->isPointerToPointer()) {
		Type *ty = buildTypes->llvmType(symbol->getDataType())->getPointerTo();	
		sym = Builder->CreateLoad(ty, sym, symbol->hasQualifier(qvolatile), "deref");
	}

	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value *indexList[2] = {zero, indice};
	Value *ptr = Builder->CreateGEP(arrayTy, sym, ArrayRef<Value*>(indexList), "gep");
	StoreInst *store = Builder->CreateStore(val, ptr, false);
	
	return store;
}
