#include "Header.h"

Value *Int64::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt64Ty(global_context), number);
}

void Int64::accept(Visitor &v) {
	v.visit(*this); 
}

