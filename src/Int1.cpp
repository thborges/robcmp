
#include "Int1.h"

Value *Int1::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
	return ConstantInt::get(Type::getInt1Ty(global_context), value);
}
