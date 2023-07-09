#include "Header.h"

	Value *Return::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		IRBuilder<> builder(block);
		Value *ret = node->generate(func, block, allocblock);
		Type *retty = func->getReturnType();
		ret = Coercion::Convert(ret, retty, block, this);
		return builder.CreateRet(ret);
	}
