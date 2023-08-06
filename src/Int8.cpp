
#include "Int8.h"

Value *Int8::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
	return ConstantInt::get(Type::getInt8Ty(global_context), number, IsSigned);
}
