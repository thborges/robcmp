#include "Header.h"

Value *Float::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getFloatTy(global_context), number);
}

