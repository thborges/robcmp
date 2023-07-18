#include "Header.h"

LanguageDataType Load::getResultType(BasicBlock *block, BasicBlock *allocblock) {
	auto rsym = search_symbol(ident, allocblock, block);
	if (rsym)
		return rsym->dt;
	return tvoid;
}

Value* Load::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	auto rsym = search_symbol(ident, allocblock, block);
	if (rsym == NULL) {
		yyerrorcpp("Variable " + ident + " not defined.", this);
		return NULL;
	}

	auto sym = rsym->value;
	if (rsym->qualifier == qconst)
		return sym;

	if (block == NULL && (allocblock == NULL || allocblock == global_alloc)) {
		// trying to load a variable to initialize a global one.
		// permitted only for const globals
		if (rsym->qualifier != qconst) {
			yyerrorcpp("Can't not use '" + ident + "' to define another var/const in global context.", this);
			return NULL;
		}
	}

	Type *ty;
	bool vol = rsym->qualifier == qvolatile;
	if (auto *lvalue = dyn_cast<AllocaInst>(sym))
		ty = lvalue->getAllocatedType();
	else if (auto *lvalue = dyn_cast<GlobalVariable>(sym))
		ty = lvalue->getValueType();
	else if (rsym->pointerType != NULL)
		ty = rsym->pointerType;
	else {
		printf("ERR: Going to return NULL!\n");
	}
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	return Builder->CreateLoad(ty, sym, vol, ident);
}

void Load::accept(Visitor &v) {
	v.visit(*this); 
}

bool Load::isConstExpr(BasicBlock *block, BasicBlock *allocblock) {
	RobSymbol *rsym = search_symbol(ident, block, allocblock);
	return rsym && (dyn_cast<Constant>(rsym->value) != NULL);
}
