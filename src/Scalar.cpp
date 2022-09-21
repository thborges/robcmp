#include "Header.h"

Scalar::Scalar(const char *n, Node *e) : name(n), expr(e) {
	node_children.reserve(1);
	node_children.push_back(e);
}

Value *Scalar::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	// generate code to produce the new variable value
	Value *exprv = expr->generate(func, block, allocblock);

	Value *leftv = search_symbol(name, allocblock, block);	
	Type *leftvty = exprv->getType();
	if (leftv == NULL) {
		if (allocblock == global_alloc) {
			GlobalVariable *gv = new GlobalVariable(*mainmodule, exprv->getType(), 
				false, GlobalValue::CommonLinkage, NULL, name);
			if (exprv->getType()->isIntegerTy())
				gv->setInitializer(ConstantInt::get(exprv->getType(), 0));
			else if (exprv->getType()->isFloatTy())
				gv->setInitializer(ConstantFP::get(exprv->getType(), 0.0));
			else if (exprv->getType()->isHalfTy())
				gv->setInitializer(ConstantFP::get(exprv->getType(), 0.0));
			else {
				yyerrorcpp("Global variable default initialization not defined: " + 
					getTypeName(exprv->getType()));
			}

			leftv = gv;
		} else {
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
		}
		tabelasym[allocblock][name] = leftv; 
	}

	/*if (leftv->getLoadStoreType()->isIntegerTy() && 
		exprv->getType()->isFloatTy()) {
		nvalue = new FPToSIInst(exprv, leftv->getLoadStoreType(), "truncistore", block);
	}*/
	auto nvalue = Coercion::Convert(exprv, leftvty, block);
	StoreInst *ret = new StoreInst(nvalue, leftv, false, block);
	return ret;

}

void Scalar::accept(Visitor& v) {
	v.visit(*this);
}

