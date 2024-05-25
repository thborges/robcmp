
#include "UpdateArray.h"
#include "Coercion.h"
#include "Array.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"

UpdateArray::UpdateArray(const char *i, Node *pos, Node *expr): ident(i), position(pos), expr(expr) {
	addChild(pos);
	addChild(expr);
}

Value *UpdateArray::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	bool localarr = false;
	Node *symbol = ident.getSymbol(getScope());
	LinearDataStructure *arr = dynamic_cast<LinearDataStructure*>(symbol);
	if (!arr) {
		// when the array has been assigned to another var
		if (buildTypes->isArray(symbol->getDataType())) {
			localarr = true;
			arr = new ParamArray(ident.getFullName(), symbol->getDataType());
			arr->setAlloca(symbol->getLLVMValue(NULL));
			arr->setPointerToPointer(symbol->isPointerToPointer());
		}
	}

	if (symbol == NULL)
		return NULL;

	Value *sym = symbol->getLLVMValue(func);

	// sym type can be GlobalVariable or AllocInst
	Type *ty = NULL;
	if (auto *aux = dyn_cast<AllocaInst>(sym))
		ty = aux->getAllocatedType();
	else if (auto *aux = dyn_cast<GlobalVariable>(sym))
		ty = aux->getValueType();

	ArrayType *arrayTy = NULL;
	if (buildTypes->isArray(symbol->getDataType())) {
		arrayTy = (ArrayType*)buildTypes->llvmType(symbol->getDataType());
	}
	else {
		yyerrorcpp("Symbol " + ident.getFullName() + " is not an array.", this);
		return NULL;
	}

	Node *indn = getElementIndex(arr);
	Value *indice = indn->generate(func, block, allocblock);
	if (!indice || !indice->getType()->isIntegerTy()){
		yyerrorcpp("Index to update " + ident.getFullName() + " elements must be of type integer.", this);
		return NULL;
	}

	Value *val = expr->generate(func, block, allocblock);
	val = Coercion::Convert(val, arrayTy->getArrayElementType(), block, this);

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

	if (localarr)
		delete arr;
	
	return store;
}

