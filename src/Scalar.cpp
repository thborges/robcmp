
#include "Scalar.h"
#include "Coercion.h"
#include "FunctionImpl.h"
#include "BackLLVM.h"
#include "Pointer.h"

Scalar::Scalar(Identifier ident, Node *e) :
	Variable(ident.getFullName()), expr(e) {
	addChild(e);
}

Scalar::Scalar(const char* ident, Node *e): Variable(ident), expr(e) {
	addChild(e);
}

Value *Scalar::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	RobDbgInfo.emitLocation(this);

	Node *symbol = ident.getSymbol(getScope());
	if (!symbol)
		return NULL;

	Pointer *reg = NULL;
	Node *stem = NULL;
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		stem = istem.getSymbol(getScope());

		// Pointers need to load the stem, get its alloc
		reg = dynamic_cast<Pointer*>(stem);
		if (reg && buildTypes->isComplex(reg->getDataType())) {
			alloc = reg->getLLVMValue(NULL);
		} else {
			alloc = symbol->getLLVMValue(stem);
		}
		
		if (stem->hasQualifier(qvolatile))
			symbol->setQualifier(qvolatile);

		// TODO: When accessing a.x.func(), need to load a and gep x
		//Load loadstem(ident.getStem());
		//loadstem.setParent(this->parent);
		//stem = loadstem.generate(func, block, allocblock);
	} else {
		alloc = symbol->getLLVMValue(func);
	}

	// tell the allocated left value to an eventual
	// constructor initializing a user type field
	if (getGEPIndex() != -1)
		expr->setLeftValue(alloc, name);

	Value *exprv = expr->generate(func, block, allocblock);
	if (!exprv)
		return NULL;
	DataType exprv_dt = expr->getDataType();

	// is the result of a constructor()?
	Value *allocall = dyn_cast<AllocaInst>(exprv);
	if (!allocall)
		allocall = dyn_cast<GetElementPtrInst>(exprv);

	if (allocall) {
		setDataType(exprv_dt);
		alloc = allocall;
		if (debug_info)
			RobDbgInfo.declareVar(this, alloc, allocblock);
	}

	// variable not allocated
	if (alloc == NULL) {
		Value *ret;
		setDataType(exprv_dt);

		auto sp = RobDbgInfo.currScope();
		auto funit = RobDbgInfo.currFile();

		if (allocblock == global_alloc) {
			Constant *exprvc = dyn_cast<Constant>(exprv);
			if (exprvc == NULL)
				return NULL; //TODO: semantic error, global const value can't be generated

			if (symbol->hasQualifier(qconst))
				ret = alloc = exprvc;
			else {
				GlobalVariable *gv = new GlobalVariable(*mainmodule, buildTypes->llvmType(dt),
					false, GlobalValue::InternalLinkage, exprvc, name);
				gv->setDSOLocal(true);
				ret = alloc = gv;

				if (debug_info) {
					auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
						funit, getLineNo(), buildTypes->diType(dt), false);
					gv->addDebugInfo(d);
				}
			}
		} else {
			Builder->SetInsertPoint(allocblock);
			AllocaInst *temp = Builder->CreateAlloca(exprv->getType(), dataAddrSpace, 0, name);
			temp->setAlignment(Align(1));
			alloc = temp;
			Builder->SetInsertPoint(block);
			ret = Builder->CreateStore(exprv, alloc, symbol->hasQualifier(qvolatile));
			
			if (debug_info)
				RobDbgInfo.declareVar(this, alloc, allocblock);
		}

		return ret;

	} else { // variable already allocated
		
		if (symbol->hasQualifier(qconst) && !func->isConstructor()) {
			yyerrorcpp("Constant '" + symbol->getName() + "' can not be changed.", this);
			return NULL;
		}

		Type *currty = buildTypes->llvmType(symbol->getDataType());
		Builder->SetInsertPoint(block);

		if (allocall) {
			// constructor result
			return allocall;

		} else {
			Value *nvalue;

			// Pointers need a custom procedure: load the stem, set the
			// requested bit value through bit shifting, and store the new value
			if (reg && buildTypes->isComplex(reg->getDataType())) {		
				/* this code does:
				*   symbol->value &= ~(0x11... << fieldStartBit)
				*   symbol->value |= (exprv << fieldStartBit)
				*/
				Type *req_eq_ty = Type::getIntNTy(global_context, buildTypes->bitWidth(reg->getDataType()));
				Value *v = Builder->CreateLoad(req_eq_ty, alloc, reg->hasQualifier(qvolatile), "ptrvalue");

				// Prepare the mask
				unsigned bitWidth = buildTypes->bitWidth(symbol->getDataType());
				Constant *allone = Constant::getAllOnesValue(Type::getIntNTy(global_context, bitWidth));
				Constant *ones = ConstantExpr::getZExt(allone, req_eq_ty);

				// Coerce the rvalue to the req size
				exprv = Coercion::Convert(exprv, req_eq_ty, block, expr);
				exprv = Builder->CreateAnd(exprv, ones, "truncrval");

				unsigned fieldStartBit = reg->getFieldStartBit(symbol);
				if (fieldStartBit > 0) {
					Constant *shiftl = ConstantInt::get(req_eq_ty, fieldStartBit);
					ones = ConstantExpr::getShl(ones, shiftl);
					exprv = Builder->CreateShl(exprv, shiftl, "shift");
				}
				Constant *mask = ConstantExpr::getNot(ones);

				// Apply mask, than or
				Value *vaftermask = Builder->CreateAnd(v, mask, "mask");
				nvalue = Builder->CreateOr(vaftermask, exprv, "setbits");

			} else {
				nvalue = Coercion::Convert(exprv, currty, block, expr);
			}

			return Builder->CreateStore(nvalue, alloc, symbol->hasQualifier(qvolatile));
		}
	}
}

Value *Scalar::getLLVMValue(Node *stem) {
	int gepidx = getGEPIndex();
	if (gepidx != -1) {
		Value *zero = ConstantInt::get(Type::getInt32Ty(global_context), 0);
		Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), gepidx);
		Value* indexList[2] = {zero, idx};
		
		if (FunctionImpl *func = dynamic_cast<FunctionImpl*>(stem)) {
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

DataType Scalar::getDataType() {
	if (dt == BuildTypes::undefinedType)
		return dt = expr->getDataType();
	else
		return dt;
}
