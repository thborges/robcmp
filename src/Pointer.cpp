
#include "Pointer.h"

Value *Pointer::generate(Function *func, BasicBlock *block, BasicBlock *allocblock)
{
    Type *ty = robTollvmDataType[type];
    ConstantInt* addr = ConstantInt::get(Type::getInt64Ty(global_context), address);
    auto leftv = ConstantExpr::getIntToPtr(addr, Type::getInt64PtrTy(global_context)); // TODO: What is the method to get an opaque pointer type?
    tabelasym[allocblock][name] = new RobSymbol(leftv, isVolatile, ty);
    return leftv;
}

void Pointer::accept(Visitor &v) {
	v.visit(*this); 
}

