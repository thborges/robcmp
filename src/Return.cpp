
#include "Return.h"
#include "FunctionImpl.h"

Value *Return::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *retvalue = NULL;
	if (value()) {
		retvalue = value()->generate(func, block, allocblock);
		if (Instruction *ins = dyn_cast<Instruction>(retvalue))
			block = ins->getParent();
	}
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	return Builder->CreateRet(retvalue);
}
