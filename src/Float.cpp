
#include "Float.h"

Value *Float::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getFloatTy(global_context), number);
}

