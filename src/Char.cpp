
#include "Char.h"

Value *Char::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
	return ConstantInt::get(Type::getInt8Ty(global_context), value);
}
