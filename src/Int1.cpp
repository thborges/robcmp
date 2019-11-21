
#include "Header.h"

Value *Int1::generate(Function *func, BasicBlock *block, BasicBlock *allocblock)
{
	return ConstantInt::get(Type::getInt1Ty(global_context), number);
}

void Int1::accept(Visitor &v) {
	v.visit(*this); 
}

