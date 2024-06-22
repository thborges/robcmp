
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
			DataType thisDt = func->getThisArgDt();
			Type *thisTy = buildTypes->llvmType(thisDt);
			Value *thisptr = Builder->CreateLoad(thisTy->getPointerTo(), func->getThisArg(), "derefthis");
			if (!stem->getScope() || this->getScope() == stem->getScope()) {
				// the var is being accessed in global scope (!stem->getScope()) or
				// in a method of the type itself. Thus, we :this and gep the field
				alloc = Builder->CreateStructGEP(thisTy, thisptr, gepidx, "gepthis");
			} else {
				// this var is in the parent scope. :this is an nested type.
				// Thus, we access :parent in :this and gep the field
				DataType parentDt = this->getScope()->getDataType();
				Type *parentTy = buildTypes->llvmType(parentDt);
				int idxParentInThis = static_cast<Variable*>(symbols["parent"])->getGEPIndex();
				Value *parentAlloc = Builder->CreateStructGEP(parentTy, thisptr, idxParentInThis, "gepthis");
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
