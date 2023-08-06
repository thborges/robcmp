
#include "Return.h"
#include "Coercion.h"
#include "FunctionImpl.h"

Value *Return::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	Value *ret = NULL;
	if (node) {
		ret = node->generate(func, block, allocblock);
		if (ret) {
			Type *retty = func->getLLVMFunction()->getReturnType();
			ret = Coercion::Convert(ret, retty, block, this);
		}
	}
	return Builder->CreateRet(ret);
}
