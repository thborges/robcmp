#include "Header.h"

	Value *Return::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		RobDbgInfo.emitLocation(this);
		Builder->SetInsertPoint(block);
		Value *ret = node->generate(func, block, allocblock);
		Type *retty = func->getReturnType();
		ret = Coercion::Convert(ret, retty, block, this);
		return Builder->CreateRet(ret);
	}
