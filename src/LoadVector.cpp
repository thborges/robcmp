#include "Header.h"

Value *LoadVector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		/* TODO */
		/* 
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}*/
		Type* I = IntegerType::getInt32Ty(global_context); 
		ArrayType* arrayType = ArrayType::get(I, 2);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		Value *um = ConstantInt::get(Type::getInt8Ty(global_context), 1);

		Value* indexList[2] = {zero, um};
		GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, sym, ArrayRef<Value*>(indexList), "", block);
		LoadInst *ret = new LoadInst(arrayType, gep, ident, block);

	//	return NULL;
		return ret;
}

