
#include "Load.h"
#include "HeaderExternals.h"
#include "Scalar.h"
#include "FunctionImpl.h"
#include "Variable.h"

DataType Load::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		Node *rsym = ident.getSymbol(getScope());
		if (rsym) {
			dt = rsym->getDataType();
		}
	}
	return dt;
}

Value* Load::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	Node *isymbol = ident.getSymbol(getScope());
	if (isymbol->isConstExpr())
		return isymbol->getLLVMValue(func);
	
	Variable *symbol = dynamic_cast<Variable*>(isymbol);
	if (!symbol)
		return NULL;

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
	
	Value *alloc;
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

	if (!alloc)
		return NULL; // Caused by an error on previous statement that defines the symbol
	
	if (buildTypes->isComplex(symbol->getDataType()))
		return alloc;
	else {
		Type *ty = buildTypes->llvmType(symbol->getDataType());
		return Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), ident.getFullName());
	}

	/*if (complexIdent) {
		// this code does:
		//   v = symbol->value << pointerbits - field_start - field_width
		//   v = v >> pointer_bits - field_width
		//

		int bs = buildTypes->bitWidth(rsym->dt) - field.bitWidth;
		if (bs - field.startBit > 0)
			v = Builder->CreateShl(v, ConstantInt::get(ty, bs - field.startBit));
		if (bs > 0)
			v = Builder->CreateAShr(v, ConstantInt::get(ty, bs));
		v = Builder->CreateTrunc(v, buildTypes->llvmType(field.fieldDataType));
	}*/
}

bool Load::isConstExpr() {
	Variable *symbol = dynamic_cast<Variable*>(ident.getSymbol(getScope()));
	return symbol && symbol->isConstExpr();
}
