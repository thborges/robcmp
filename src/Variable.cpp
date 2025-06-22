
#include "Variable.h"
#include "FunctionImpl.h"
#include "Scalar.h"

Value *Variable::getLLVMValue(Node *stem, FunctionImpl *gfunc) {
	int gepidx = getGEPIndex();
	if (gepidx != -1) {
		Value *zero = ConstantInt::get(Type::getInt32Ty(global_context), 0);
		Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), gepidx);
		Value* indexList[2] = {zero, idx};
		
		FunctionImpl *func = dynamic_cast<FunctionImpl*>(stem);
		if (func && func->getThisArg()) {
			// generating a function of a type: get the gep on _this or _parent parameters
			DataType thisDt = func->getThisArgDt();
			Type *thisTy = buildTypes->llvmType(thisDt);
			Value *thisptr = Builder->CreateLoad(PointerType::getUnqual(thisTy), func->getThisArg(), "derefthis");
			
			if (!stem->getScope() || this->getScope() == stem->getScope()) {
				// the var is being accessed in global scope (!stem->getScope()) or
				// in a method of the type itself. Thus, we gep the field in _this argument
				return Builder->CreateStructGEP(thisTy, thisptr, gepidx, "gep" + getName());

			} else if (symbols.find("parent") != symbols.end()) {
				// the symbol being accessed has a parent (acessing a nested type var or method)
				// Thus, we access parent in _this and gep the field
				DataType parentDt = this->getScope()->getDataType();
				Type *parentTy = buildTypes->llvmType(parentDt);
				NamedNode *parent = symbols["parent"];
				Scalar *parentscalar = dynamic_cast<Scalar*>(parent);
				parentscalar->setUsed(true);
				int idxParentInThis = static_cast<Variable*>(parent)->getGEPIndex();
				Value *parentAlloc = Builder->CreateStructGEP(parentTy, thisptr, idxParentInThis, "gepthis");
				Value *parentptr = Builder->CreateLoad(PointerType::getUnqual(parentTy), parentAlloc, "derefparent");
				return Builder->CreateStructGEP(parentTy, parentptr, gepidx, "gep" + getName());

			} else {
				// stem is a nested type and the var is in the parent scope.
				// Thus, we access parent in stem and gep the field
				Node *nestedType = stem->getScope();
				auto nestedSymbols = nestedType->getSymbols();
				Node *parentField = nestedSymbols.find("parent")->second;
				Scalar *parentFieldVar = dynamic_cast<Scalar*>(parentField);
				parentFieldVar->setUsed(true);
				assert(parentField && "Parent field must exists and have a gepIndex!");
				int idxParentInThis = parentFieldVar->getGEPIndex();
				Type *parentTy = buildTypes->llvmType(parentFieldVar->getDataType());
				Value *parentAlloc = Builder->CreateStructGEP(parentTy, thisptr, idxParentInThis, "gepparent");
				Value *parentptr = Builder->CreateLoad(PointerType::getUnqual(parentTy), parentAlloc, "derefparent");
				return Builder->CreateStructGEP(parentTy, parentptr, gepidx, "gep" + getName());
			}
		} else {
			// accessing a var of a user type: get the gep in the scope (user type) of the scalar
			Type *udt = buildTypes->llvmType(stem->getDataType());
			Value *ptr = stem->getLLVMValue(gfunc);
			if (stem->isPointerToPointer()) {
				ptr = Builder->CreateLoad(PointerType::getUnqual(udt), ptr, "deref");
			}
			return Builder->CreateStructGEP(udt, ptr, gepidx, "gepu");
		}
	}

	if (!alloc && isConstExpr())
		return generate(NULL, NULL, NULL);

	return alloc;
}
