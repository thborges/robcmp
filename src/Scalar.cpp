#include "Header.h"

Scalar::Scalar(const char *n, Node *e, DataQualifier qualifier) : 
	name(n), expr(e), qualifier(qualifier) {
	node_children.reserve(1);
	node_children.push_back(e);
}

Value *Scalar::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

	auto symbol = search_symbol(name, allocblock, block);

	// variable doesn't exists
	if (symbol == NULL) {
		Value *ret, *leftv;
		Value *exprv = expr->generate(func, block, allocblock);
		if (!exprv)
			return NULL;
		
		if (allocblock == global_alloc) {
			Constant *exprvc = dyn_cast<Constant>(exprv);
			if (exprvc == NULL)
				return NULL; //TODO: semantic error, global const value can't be generated

			if (qualifier == qconst)
				ret = leftv = exprvc;
			else {
				GlobalVariable *gv = new GlobalVariable(*mainmodule, exprvc->getType(), 
					false, GlobalValue::CommonLinkage, exprvc, name);
				ret = leftv = gv;
			}
		} else {
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
			ret = new StoreInst(exprv, leftv, qualifier == qvolatile, block);
		}

		tabelasym[allocblock][name] = new RobSymbol(leftv, qualifier);
		return ret;

	} else {
		if (symbol->qualifier == qconst) {
			yyerrorcpp("Constant '" + name + "' can not be changed.", this);
			return NULL;
		}
		// variable already exists
		Type *leftvty = symbol->value->getType();
		qualifier = symbol->qualifier;
		if (symbol->pointerType)
			leftvty = symbol->pointerType;
		Value *exprv = expr->generate(func, block, allocblock);
		auto nvalue = Coercion::Convert(exprv, leftvty, block, expr);
		return new StoreInst(nvalue, symbol->value, qualifier == qvolatile, block);
	}
}

void Scalar::accept(Visitor& v) {
	v.visit(*this);
}
