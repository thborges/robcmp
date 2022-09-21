#include "Header.h"

Value *LoadMatrix::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		/* TODO */
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}

		// sym type can be GlobalVariable or AllocInst
		Type *ty = NULL;
		if (auto *aux = dyn_cast<AllocaInst>(sym))
			ty = aux->getAllocatedType();
		else if (auto *aux = dyn_cast<GlobalVariable>(sym))
			ty = aux->getValueType();
		
		ArrayType *arrayTy = NULL;
		Type *matrixTy = NULL;
		if (ty->isArrayTy()) {
			arrayTy = (ArrayType*)ty;
			matrixTy = arrayTy->getElementType();
		}
		else {
			yyerrorcpp("Symbol " + ident + " is not of matrix or array type.");
			return NULL;
		}
		
		//Generate first param.
		Value *indice = position_1->generate(func, block, allocblock);
		if (!indice->getType()->isIntegerTy()){
			yyerrorcpp("Index for " + ident + " line should be of integer type.");
			return NULL;
		}

		//Generate second param.
		Value *indice_2 = position_2->generate(func, block, allocblock);
		if (!indice_2->getType()->isIntegerTy()){
			yyerrorcpp("Index for " + ident + " column should be of integer type.");
			return NULL;
		}

		//Get Vector in Matrix
		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		Value* indexList[2] = {zero, indice};
		GetElementPtrInst* ptr = GetElementPtrInst::CreateInBounds(arrayTy, sym, ArrayRef<Value*>(indexList), "gepl"+ident, block);
//		LoadInst *l = new LoadInst(ptr, ident, false, block);

		//Get Element in Vector
		Value* indexList2[2] = {zero, indice_2};
		GetElementPtrInst* gep = GetElementPtrInst::Create(matrixTy, ptr, ArrayRef<Value*>(indexList2), "gepc"+ident, block);
		LoadInst *ret = new LoadInst(gep->getResultElementType(), gep, "lc"+ident, false, block);

		return ret;
}

