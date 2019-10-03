#include "Header.h"

Value *Int32::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt32Ty(global_context), number);
}

void Int32::accept(Visitor &v) {
	v.visit(*this); 
}

