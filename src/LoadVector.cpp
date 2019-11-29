#include "Header.h"

Value *LoadVector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
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
			yyerrorcpp("Index for " + ident + " vector should be of integer type.");
			return NULL;
		}

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		//Value *indice = ConstantInt::get(Type::getInt8Ty(global_context), npos);

		Value* indexList[2] = {zero, indice};
		//GetElementPtrInst* ptr = GetElementPtrInst::Create(Type *PointeeType, Value *Ptr, ArrayRef<Value*> IdxList, const Twine &NameStr="", Instruction/BasicBlock *Insert)
		GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayTy, sym, ArrayRef<Value*>(indexList), "", block);
//		GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, sym, ArrayRef<Value*>(indexList), "", block);
		LoadInst *ret = new LoadInst(ptr, ident, false, block);

		return ret;
	//	return ret;
}

