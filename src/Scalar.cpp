
#include "Scalar.h"
#include "Coercion.h"
#include "FunctionImpl.h"
#include "BackLLVM.h"

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

	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *stem = istem.getSymbol(getScope());
		alloc = symbol->getLLVMValue(stem);
		
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
					false, GlobalValue::CommonLinkage, exprvc, name);
				//gv->setDSOLocal(true);
				ret = alloc = gv;

				if (debug_info) {
					auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
						funit, getLineNo(), buildTypes->diType(dt), false);
					gv->addDebugInfo(d);
				}
			}
		} else {
			Builder->SetInsertPoint(allocblock);
			AllocaInst *temp = Builder->CreateAlloca(exprv->getType(), globalAddrSpace, 0, name);
			temp->setAlignment(Align(1));
			alloc = temp;
			Builder->SetInsertPoint(block);
			ret = Builder->CreateStore(exprv, alloc, symbol->hasQualifier(qvolatile));
			
			if (debug_info)
				RobDbgInfo.declareVar(this, alloc, allocblock);
		}

		return ret;

	} else { // variable already allocated
		
		if (symbol->hasQualifier(qconst)) {
			yyerrorcpp("Constant '" + symbol->getName() + "' can not be changed.", this);
			return NULL;
		}

		Type *currty = buildTypes->llvmType(symbol->getDataType());
		Builder->SetInsertPoint(block);

		/*
		if (complexIdent) {
			// this code does:
			//   symbol->value &= ~(0x11... << field.startBit)
			//   symbol->value |= (exprv << field.startBit)
			//

			// Coerce the left side to the field size
			exprv = Coercion::Convert(exprv, buildTypes->llvmType(field.fieldDataType), block, expr);
			// Expand to the left side size
			exprv = Coercion::Convert(exprv, leftvty, block, expr);
			
			// Prepare the mask
			Constant *allone = Constant::getAllOnesValue(Type::getIntNTy(global_context, field.bitWidth));
			Constant *ones = ConstantExpr::getZExt(allone, leftvty);

			if (field.startBit > 0) {
				Constant *shiftl = ConstantInt::get(leftvty, field.startBit);
				ones = ConstantExpr::getShl(ones, shiftl);
				exprv = Builder->CreateShl(exprv, shiftl, "shift");
			}
			Constant *mask = ConstantExpr::getNot(ones);

			// Load pointer value
			Load ld(id);
			ld.setLocation(expr);
			Value *leftv = ld.generate(func, block, allocblock);

			// Apply mask, than or
			Builder->SetInsertPoint(block); //caution, after generate!
			Value *vaftermask = Builder->CreateAnd(leftv, mask, "mask");
			nvalue = Builder->CreateOr(vaftermask, exprv, "setbits");
		} else {*/
		
		// TODO: remove this check after converting Coercion to use DataType
		//       instead of llvm::Type
		Value *nvalue;
		if (allocall)
			return allocall;
		else {
			nvalue = Coercion::Convert(exprv, currty, block, expr);
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
