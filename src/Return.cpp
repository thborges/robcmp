
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
			DataType sdt = node->getDataType();
			if (buildTypes->isComplex(sdt)) {
				// defer the pointer before returning
				Type *ty = buildTypes->llvmType(sdt);
				ret = Builder->CreateLoad(ty, ret, false, "deref");
			}
			Type *retty = func->getLLVMFunction()->getReturnType();
			ret = Coercion::Convert(ret, retty, block, this);
		}
	}
	return Builder->CreateRet(ret);
}
