
#include "BitCast.h"

Value *BitCast::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
    Value *v = value->generate(func, block, allocblock);
    Type *dTy = buildTypes->llvmType(destTy);
	return Builder->CreateBitCast(v, dTy);
}
