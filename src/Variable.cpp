
#include "Variable.h"
#include "FunctionImpl.h"

Value *Variable::getLLVMValue(Node *stem) {
	int gepidx = getGEPIndex();
	if (gepidx != -1) {
		Value *zero = ConstantInt::get(Type::getInt32Ty(global_context), 0);
		Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), gepidx);
		Value* indexList[2] = {zero, idx};
		
		FunctionImpl *func = dynamic_cast<FunctionImpl*>(stem);
		if (func && func->getThisArg()) {
			// generating a function of a type: get the gep on the #this parameter
			Type *thisTy = buildTypes->llvmType(func->getThisArgDt());
			alloc = Builder->CreateStructGEP(thisTy, func->getThisArg(), gepidx, "gepthis");
		} else {
			// accessing a var of a user type: get the gep in the scope (user type) of the scalar
			Type *udt = buildTypes->llvmType(stem->getDataType());
			alloc = Builder->CreateStructGEP(udt, stem->getLLVMValue(NULL), gepidx, "gepu"); // FIXME
		}
	}
	return alloc;
}
