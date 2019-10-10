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
		ArrayType* arrayType = ArrayType::get(I, 10);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		Value *indice = ConstantInt::get(Type::getInt8Ty(global_context), 1);

		Value* indexList[2] = {zero, indice};
		//GetElementPtrInst* ptr = GetElementPtrInst::Create(Type *PointeeType, Value *Ptr, ArrayRef<Value*> IdxList, const Twine &NameStr="", Instruction/BasicBlock *Insert)
		GetElementPtrInst* ptr = GetElementPtrInst::Create(arrayType, sym, ArrayRef<Value*>(indexList), "", block);
//		GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, sym, ArrayRef<Value*>(indexList), "", block);
		LoadInst *ret = new LoadInst(ptr, ident, false, block);

		return ret;
	//	return ret;
}

