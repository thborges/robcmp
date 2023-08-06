
#include "Int32.h"

Value *Int32::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantInt::get(Type::getInt32Ty(global_context), number, IsSigned);
}
