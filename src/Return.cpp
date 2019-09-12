#include "Header.h"

	Value *Return::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		IRBuilder<> builder(block);
		Value *ret = node->generate(func, block, allocblock);
		return builder.CreateRet(ret);
	}
