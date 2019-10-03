#include "Header.h"
#include "Int16.h"

Value *Int16::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt16Ty(global_context), number);
}

void Int16::accept(Visitor &v) {
	v.visit(*this); 
}

