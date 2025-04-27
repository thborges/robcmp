
#include "Scalar.h"
#include "FunctionImpl.h"
#include "BackLLVM.h"
#include "HeaderGlobals.h"
#include "Pointer.h"
#include "Load.h"

Scalar::Scalar(Identifier ident, Node *e) :
	Variable(ident.getFullName(), ident.getLoc()) {
	addChild(e);
}

Scalar::Scalar(const string& ident, Node *e): Variable(ident, e->getLoc()) {
	addChild(e);
}

Value *Scalar::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	Node *isymbol = ident.getSymbol(getScope());
	Variable *symbol = dynamic_cast<Variable*>(isymbol);
	if (!symbol)
		return NULL;

	Builder->SetInsertPoint(block);
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
			alloc = Load::getRecursiveField(ident, getScope(), func);
		}
		
		if (stem->hasQualifier(qvolatile))
			symbol->setQualifier(qvolatile);
	}

	// set the allocated left value to:
	//  - a constructor initializing a user type field
	//  - a load for a new variable
	Node *expr = getExpr();
	expr->setLeftValue(symbol);

	Value *exprv = expr->generate(func, block, allocblock);
	if (!exprv)
		return NULL;
	else {
		// A distinct block can return from boolean short-circuit evaluation
		Instruction* instr = dyn_cast<Instruction>(exprv);
		if (instr && instr->getParent() != allocblock)
			block = instr->getParent();
	}
	DataType exprv_dt = expr->getDataType();

	if (hasQualifier(qconst))
		return exprv;

	Builder->SetInsertPoint(block);
	if (!alloc)
		alloc = symbol->getLLVMValue(func);
	
	// variable not allocated
	if (alloc == NULL) {
		Value *ret = NULL;
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
				Type *gty = buildTypes->llvmType(dt);
				if (expr->isPointerToPointer()) {
					setPointerToPointer(true);
					gty = gty->getPointerTo();
				}
				GlobalVariable *gv = new GlobalVariable(*mainmodule, gty, hasQualifier(qconst), 
					GlobalValue::ExternalLinkage, exprvc, name);
				ret = alloc = gv;

				if (debug_info)
					RobDbgInfo.declareGlobalVar(expr, gv, allocblock);
			}
		} else {
			RobDbgInfo.emitLocation(this);
			Builder->SetInsertPoint(allocblock);
			AllocaInst *temp = Builder->CreateAlloca(exprv->getType(), dataAddrSpace, 0, name);
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
		
		DataType currdt = symbol->getDataType();
		enum PointerMode pm = symbol->getPointerMode();

		if (buildTypes->isComplex(currdt)) {
			if (pm == pm_unknown) {
				symbol->setPointer(pm_pointer);
				pm = pm_pointer;

			} else if (pm == pm_nopointer && !func->isConstructor() &&
				exprv->getType()->isPointerTy()) {
				// as any complex type is passed by ref, one must deref it before assigning
				// to leftv, using the copy operator.
				yyerrorcpp("Use the copy operator to dereference the rvalue.", this);
				return NULL;
			}
		}

		Type *currty = buildTypes->llvmType(currdt);
		if (pm == pm_pointer)
			currty = currty->getPointerTo();

		RobDbgInfo.emitLocation(this);
		Builder->SetInsertPoint(allocblock == global_alloc ? global_alloc : block);
		Value *nvalue = NULL;

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
			Value *ones = Builder->CreateZExt(allone, req_eq_ty);

			// Coerce the rvalue to the req size
			exprv = Builder->CreateZExt(exprv, req_eq_ty);
			exprv = Builder->CreateAnd(exprv, ones, "truncrval");

			unsigned fieldStartBit = reg->getFieldStartBit(symbol);
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
			RobDbgInfo.emitLocation(this);
			const DataLayout &DL = mainmodule->getDataLayout();
			Align align = DL.getABITypeAlign(nvalue->getType());
			return Builder->CreateAlignedStore(nvalue, alloc, align, symbol->hasQualifier(qvolatile));
		} else 
			return nvalue;
	}
}

DataType Scalar::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		if (ident.isComplex()) {
			Node *symbol = ident.getSymbol(getScope(), false);
			if (symbol)
				dt = symbol->getDataType();
		} else
			dt = getExpr()->getDataType();
	}
	return dt;
}
