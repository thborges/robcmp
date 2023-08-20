
#include "Load.h"
#include "HeaderExternals.h"
#include "Scalar.h"
#include "FunctionImpl.h"
#include "Variable.h"
#include "Pointer.h"

DataType Load::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		Node *rsym = ident.getSymbol(getScope(), false);
		if (rsym) {
			dt = rsym->getDataType();
		}
	}
	return dt;
}

Value* Load::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	Node *isymbol = ident.getSymbol(getScope(), false);
	if (!isymbol)
		isymbol = ident.getSymbol(func, false);
	
	if (isymbol && isymbol->isConstExpr())
		return isymbol->getLLVMValue(func);
	
	Variable *symbol = dynamic_cast<Variable*>(isymbol);
	if (!symbol) {
        yyerrorcpp("Symbol " + ident.getFullName() + " not found.", this);
		return NULL;
	}

	dt = isymbol->getDataType();

	if (block == NULL && (allocblock == NULL || allocblock == global_alloc)) {
		// trying to load a variable to initialize a global one.
		// permitted only for const globals
		if (!symbol->hasQualifier(qconst)) {
			yyerrorcpp("Can not use '" + ident.getFullName() + "' to define another var/const in global context.", this);
			return NULL;
		}
	}
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	
	Value *alloc = NULL;
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *stem = istem.getSymbol(getScope());

		// Pointers need a custom procedure: load the stem and get the 
		// requested bit value through bit shifting
		Pointer *reg = dynamic_cast<Pointer*>(stem);
		if (reg && buildTypes->isComplex(reg->getDataType())) {
			alloc = reg->getLLVMValue(NULL);
			Type *req_eq_ty = Type::getIntNTy(global_context, buildTypes->bitWidth(reg->getDataType()));
			Value *v = Builder->CreateLoad(req_eq_ty, alloc, reg->hasQualifier(qvolatile), "ptrvalue");
			/* this code does:
			 *   v = symbol->value << pointerbits - field_start - field_width
			 *   v = v >> pointer_bits - field_width
			 */
			int bs = buildTypes->bitWidth(reg->getDataType()) - buildTypes->bitWidth(symbol->getDataType());
			unsigned fieldStartBit = reg->getFieldStartBit(symbol);
			if (bs - fieldStartBit > 0)
				v = Builder->CreateShl(v, ConstantInt::get(req_eq_ty, bs - fieldStartBit));
			if (bs > 0)
				v = Builder->CreateLShr(v, ConstantInt::get(req_eq_ty, bs));
			return Builder->CreateTrunc(v, buildTypes->llvmType(symbol->getDataType()));
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

	if (!alloc)
		return NULL; // Caused by an error on previous statement that defines the symbol
	
	if (buildTypes->isComplex(symbol->getDataType())) 
		return alloc;
	else {
		Type *ty = buildTypes->llvmType(symbol->getDataType());
		return Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), ident.getFullName());
	}
}

bool Load::isConstExpr() {
	Variable *symbol = dynamic_cast<Variable*>(ident.getSymbol(getScope()));
	return symbol && symbol->isConstExpr();
}
