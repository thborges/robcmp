
#include "Header.h"

Value *Int8::generate(Function *func, BasicBlock *block, BasicBlock *allocblock)
{
	return ConstantInt::get(Type::getInt8Ty(global_context), number);
}
