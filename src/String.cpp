#include "Header.h"

	Value *String::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantDataArray::getString(global_context, str, true);;
	}
