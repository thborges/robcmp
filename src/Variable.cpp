
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
			// generating a function of a type: get the gep on :this or :parent parameters
			Type *thisTy = buildTypes->llvmType(func->getThisArgDt());
			Value *thisptr = Builder->CreateLoad(thisTy->getPointerTo(), func->getThisArg(), "derefthis");
			if (!stem->getScope() || this->getScope() == stem->getScope()) {
				// in the global or same scope, defer :this and gep the field
				alloc = Builder->CreateStructGEP(thisTy, thisptr, gepidx, "gepthis");
			} else {
				// FIXME: in distinct scopes, access :parent (gep 0 or 1) in :this and gep the field
				// currently, the CreateStructGEP deference 0; but zero sometimes is the typeid var
				Type *parentTy = buildTypes->llvmType(this->getScope()->getDataType());
				Value *parentAlloc = Builder->CreateStructGEP(parentTy, thisptr, 0, "gepthis");
				Value *parentptr = Builder->CreateLoad(parentTy->getPointerTo(), parentAlloc, "derefparent");
				alloc = Builder->CreateStructGEP(parentTy, parentptr, gepidx, "gepparent");
			}
		} else {
			// accessing a var of a user type: get the gep in the scope (user type) of the scalar
			Type *udt = buildTypes->llvmType(stem->getDataType());
			Value *ptr = stem->getLLVMValue(NULL);
			if (stem->isPointerToPointer()) {
				ptr = Builder->CreateLoad(udt->getPointerTo(), ptr, "deref");
			}
			alloc = Builder->CreateStructGEP(udt, ptr, gepidx, "gepu"); // FIXME
		}
	}
	return alloc;
}
