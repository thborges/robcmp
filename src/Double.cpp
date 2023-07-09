#include "Header.h"

Value *Double::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getDoubleTy(global_context), number);
}

