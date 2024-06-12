
#include "Int16.h"

Value *Int16::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt16Ty(global_context), number, true);
}

Value *UInt16::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt16Ty(global_context), number, false);
}
