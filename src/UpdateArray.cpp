
#include "UpdateArray.h"
#include "Coercion.h"
#include "Array.h"
#include "FunctionImpl.h"

UpdateArray::UpdateArray(const char *i, Node *pos, Node *expr): ident(i), position(pos), expr(expr) {
	addChild(pos);
	addChild(expr);
}

Value *UpdateArray::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
		Node *rsym = ident.getSymbol(getScope());
		if (rsym == NULL) {
			return NULL;
		}
		LinearDataStructure *arr = dynamic_cast<LinearDataStructure*>(rsym);
		Value *sym = rsym->getLLVMValue(func);

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
			yyerrorcpp("Symbol " + ident.getFullName() + " is not an array.", this);
			return NULL;
		}

		Node *indn = getElementIndex(arr);
		Value *indice = indn->generate(func, block, allocblock);
		if (!indice || !indice->getType()->isIntegerTy()){
			yyerrorcpp("Index to update " + ident.getFullName() + " elements must be of type integer.", this);
			return NULL;
		}

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
		Value *val = expr->generate(func, block, allocblock);
		val = Coercion::Convert(val, arrayTy->getArrayElementType(), block, this);
		StoreInst *store = new StoreInst(val, ptr, false, block);

		return store;
}

