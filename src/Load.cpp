
#include "Load.h"
#include "BuildTypes.h"
#include "FunctionImpl.h"
#include "Variable.h"
#include "Pointer.h"

Node* Load::getIdentSymbol(bool showError) {
	if (!identSymbol) {
		identSymbol = ident.getSymbol(getScope(), false);
	}
	if (!identSymbol && showError)
        yyerrorcpp("Symbol " + ident.getFullName() + " not found.", this);
	return identSymbol;
}

DataType Load::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		if (getIdentSymbol())
			dt = identSymbol->getDataType();
	}
	return dt;
}

Value* Load::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	if (!identSymbol) {
		identSymbol = ident.getSymbol(getScope(), false);
		if (!identSymbol) {
			identSymbol = ident.getSymbol(func, false);
			//assert(false && "when this is executed?");//FIXME
		}
	}
	
	if (identSymbol && identSymbol->isConstExpr())
		return identSymbol->getLLVMValue(func);
	
	Variable *symbol = dynamic_cast<Variable*>(identSymbol);
	if (!symbol) {
        yyerrorcpp("Symbol " + ident.getFullName() + " not found.", this);
		return NULL;
	}

	dt = identSymbol->getDataType();

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

		// when the new var will be a reference to expr;
		// we change its scope to the scope of expr (stem)
		// this is needed by injection
		if (leftValue)
			leftValue->setScope(stem, true);
		
		// TODO: When accessing a.x.func(), need to load a and gep x
		//Load loadstem(ident.getStem());
		//loadstem.setParent(this->parent);
		//stem = loadstem.generate(func, block, allocblock);
	} else {
		alloc = symbol->getLLVMValue(func);
	}

	if (!alloc)
		return NULL; // Caused by an error on previous statement that defines the symbol
	
	DataType sdt = symbol->getDataType();
	if (buildTypes->isComplex(sdt) || buildTypes->isArrayOrMatrix(sdt)) {
		if (symbol->isPointerToPointer()) {
			Type *ty = buildTypes->llvmType(sdt)->getPointerTo();	
			alloc = Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), "deref");
		}
		if (leftValue)
			leftValue->setPointerToPointer(true);
		return alloc;
	} else {
		Type *ty = buildTypes->llvmType(sdt);
		return Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), ident.getFullName());
	}
}

bool Load::isConstExpr() {
	Node *symbol = ident.getSymbol(getScope());
	return symbol && symbol->isConstExpr();
}

void Load::setLeftValue(Variable *symbol) {
    leftValue = symbol;
}
