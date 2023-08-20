
#include "Float128.h"

Value *Float128::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantFP::get(Type::getFP128Ty(global_context), number);
}

