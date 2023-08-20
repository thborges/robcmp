
#include "StringConst.h"

Value *StringConst::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return ConstantDataArray::getString(global_context, str, true);;
}
