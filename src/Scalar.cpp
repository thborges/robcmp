#include "Header.h"

Scalar::Scalar(const char *n, Node *e, bool vol) : 
	name(n), expr(e), isVolatile(vol) {
	node_children.reserve(1);
	node_children.push_back(e);
}

Value *Scalar::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	// generate code to produce the new variable value
	Value *exprv = expr->generate(func, block, allocblock);

	auto symbol = search_symbol(name, allocblock, block);

	// variable doesn't exists
	if (symbol == NULL) {
		Value *ret, *leftv;
		bool initialized = false;

		if (allocblock == global_alloc) {
			GlobalVariable *gv = new GlobalVariable(*mainmodule, exprv->getType(), 
				false, GlobalValue::CommonLinkage, NULL, name);
			Constant *c = dyn_cast<Constant>(exprv);
			if (c) {
				gv->setInitializer(c);
				initialized = true;
			}
			ret = leftv = gv;
		} else {
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
		}

		if (!initialized)
			ret = new StoreInst(exprv, leftv, isVolatile, block);

		tabelasym[allocblock][name] = new RobSymbol(leftv, isVolatile);
		return ret;

	} else {
		// variable already exists
		Type *leftvty = symbol->value->getType();
		isVolatile = symbol->isVolatile;
		if (symbol->pointerType)
			leftvty = symbol->pointerType;
		auto nvalue = Coercion::Convert(exprv, leftvty, block);
		return new StoreInst(nvalue, symbol->value, isVolatile, block);
	}
}

void Scalar::accept(Visitor& v) {
	v.visit(*this);
}
