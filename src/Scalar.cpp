
#include "Scalar.h"
#include "FunctionImpl.h"
#include "BackLLVM.h"
#include "HeaderGlobals.h"
#include "Pointer.h"
#include "Load.h"

Scalar::Scalar(LeftValueData *lv, Node *e) : Variable(lv->ident, lv->loc) {
	leftv = lv;
	addChild(e);
	if (leftv->value)
		addChild(leftv->value);
	for(auto &[key, value] : e->getSymbols())
		symbols[key] = value;
}

Scalar::Scalar(const string& ident, location_t loc): Variable(ident, loc) {
	leftv = new LeftValueData();
	leftv->ident = ident;
}

Scalar::Scalar(const string& ident, Node *e): Variable(ident, e->getLoc()) {
	leftv = new LeftValueData();
	leftv->ident = ident;
	addChild(e);
	for(auto &[key, value] : e->getSymbols())
		symbols[key] = value;
}

Value *Scalar::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	Variable *symbol = NULL;
	bool isVolatile = false;
	if (!leftv->stem) {
		// local var
		Node *isymbol = ident.getSymbol(getScope());
		symbol = dynamic_cast<Variable*>(isymbol);
		if (!symbol)
			return NULL;
		isVolatile = symbol->hasQualifier(qvolatile);
		if (symbol != this || symbol->getGEPIndex() != -1)
			alloc = symbol->getLLVMValue(func);
	} else {
		// field var, recursive load to get the store pointer
		alloc = leftv->value->generateNewBlock(func, &block, allocblock);
		//TODO: set isVolatile
	}

	// set the allocated left value to:
	//  - a constructor initializing a user type field
	//  - a load for a new variable
	Node *expr = getExpr();
	expr->setLeftValue(this);

	Value *exprv = expr->generateNewBlock(func, &block, allocblock);
	if (!exprv)
		return NULL;
	DataType exprv_dt = expr->getDataType();

	if (hasQualifier(qconst))
		return exprv;

	// expr->generate changes the location and block
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	
	// variable not allocated
	if (alloc == NULL) {
		Value *ret = NULL;
		setDataType(exprv_dt);

		if (allocblock == global_alloc) {
			Constant *exprvc = dyn_cast<Constant>(exprv);
			if (exprvc == NULL)
				return NULL; //TODO: semantic error, global const value can't be generated

			if (symbol->hasQualifier(qconst))
				ret = alloc = exprvc;
			else {
				Type *gty = buildTypes->llvmType(dt);
				if (expr->isPointerToPointer()) {
					setPointerToPointer(true);
					gty = PointerType::getUnqual(gty);
				}
				GlobalVariable *gv = new GlobalVariable(*mainmodule, gty, hasQualifier(qconst), 
					GlobalValue::ExternalLinkage, exprvc, name);
				ret = alloc = gv;

				if (debug_info)
					RobDbgInfo.declareGlobalVar(expr, gv, allocblock);
			}
		} else {
			Builder->SetInsertPoint(allocblock);
			alloc = Builder->CreateAlloca(exprv->getType(), dataAddrSpace, 0, name);
			Builder->SetInsertPoint(block);
			ret = Builder->CreateStore(exprv, alloc, symbol->hasQualifier(qvolatile));

			if (debug_info)
				RobDbgInfo.declareVar(this, alloc, allocblock);

			if (buildTypes->isComplex(dt)) {
				setPointerToPointer(true);
			}

			// the symbol is in another scope or
			// the var is set more than once
			if (alloc && this != symbol) {
				symbol->setAlloca(alloc);
			}
		}

		return ret;

	} else { // variable already allocated

		Type *currty = buildTypes->llvmType(dt);
		Builder->SetInsertPoint(allocblock == global_alloc ? global_alloc : block);
		Value *nvalue = NULL;

		// Pointers need a custom procedure: load the stem, set the
		// requested bit value through bit shifting, and store the new value
		Node *loadSymbol = NULL;
		if (leftv->value)
			loadSymbol = leftv->value->getLoadSymbol();
		
		Pointer *reg = dynamic_cast<Pointer*>(loadSymbol);
		if (reg && buildTypes->isComplex(reg->getDataType())) {		
			/* this code does:
			 *   symbol->value &= ~(0x11... << fieldStartBit)
			 *   symbol->value |= (exprv << fieldStartBit)
			 */
			Type *req_eq_ty = Type::getIntNTy(global_context, buildTypes->bitWidth(reg->getDataType()));
			Value *v = Builder->CreateLoad(req_eq_ty, alloc, reg->hasQualifier(qvolatile), "ptrvalue");

			// Prepare the mask
			Node *member = loadSymbol->findMember(leftv->ident);
			unsigned bitWidth = buildTypes->bitWidth(member->getDataType());
			Constant *allone = Constant::getAllOnesValue(Type::getIntNTy(global_context, bitWidth));
			Value *ones = Builder->CreateZExt(allone, req_eq_ty);

			// Coerce the rvalue to the req size
			exprv = Builder->CreateZExt(exprv, req_eq_ty);
			exprv = Builder->CreateAnd(exprv, ones, "truncrval");

			unsigned fieldStartBit = reg->getFieldStartBit(leftv->ident);
			if (fieldStartBit > 0) {
				Constant *shiftl = ConstantInt::get(req_eq_ty, fieldStartBit);
				ones = Builder->CreateShl(ones, shiftl);
				exprv = Builder->CreateShl(exprv, shiftl, "shift");
			}
			Value *mask = Builder->CreateNot(ones);

			// Apply mask, than or
			Value *vaftermask = Builder->CreateAnd(v, mask, "mask");
			nvalue = Builder->CreateOr(vaftermask, exprv, "setbits");

		} else {
			nvalue = exprv;
		}

		if (nvalue != alloc) {
			const DataLayout &DL = mainmodule->getDataLayout();
			Align align = DL.getABITypeAlign(nvalue->getType());
			return Builder->CreateAlignedStore(nvalue, alloc, align, isVolatile);
		} else 
			return nvalue;
	}
}

DataType Scalar::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		if (leftv->stem) {
			// return the type of the field
			dt = leftv->value->getDataType();
		} else {
			Node *symbol = ident.getSymbol(getScope());
			if (symbol && symbol != this)
				dt = symbol->getDataType();
			
			// as dt is still undefiend, the expr defines the first type
			if (dt == BuildTypes::undefinedType)
				dt = getExpr()->getDataType();
		}
	}
	return dt;
}
