
#include "Double.h"

Value *Double::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getDoubleTy(global_context), number);
}

