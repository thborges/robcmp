#include "Header.h"

Value *Half::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getHalfTy(global_context), number);
}

