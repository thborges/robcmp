
#include "Int64.h"

Value *Int64::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt64Ty(global_context), number, true);
}

Value *UInt64::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt64Ty(global_context), number, false);
}
