#include "Header.h"

Value *Float128::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getFP128Ty(global_context), number);
}

