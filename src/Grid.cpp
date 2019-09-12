#include "Header.h"

Value *Grid::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	// generate code to produce the new variable value
	Value *exprv = expr->generate(func, block, allocblock);

	Value *leftv = search_symbol(name, allocblock, block);	
	if (leftv == NULL) {
		if (allocblock == global_alloc) {
			GlobalVariable *gv = new GlobalVariable(*mainmodule, exprv->getType(), 
				false, GlobalValue::CommonLinkage, NULL, name);
			if (exprv->getType()->isIntegerTy())
				gv->setInitializer(ConstantInt::get(exprv->getType(), 0));
			else if (exprv->getType()->isFloatTy())
				gv->setInitializer(ConstantFP::get(exprv->getType(), 0.0));
			else
				yyerrorcpp("Global variable default initialization not defined.");

			leftv = gv;
		} else {
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
		}
		tabelasym[allocblock][name] = leftv; 
	}

	auto nvalue = exprv;
	if (leftv->getType()->getPointerElementType()->isIntegerTy() && 
		exprv->getType()->isFloatTy()) {
		nvalue = new FPToSIInst(exprv, leftv->getType()->getPointerElementType(), 
			"truncistore", block);
	}
	StoreInst *ret = new StoreInst(nvalue, leftv, false, block);
	return ret;

}

