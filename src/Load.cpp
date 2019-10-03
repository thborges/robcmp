#include "Header.h"

Value *Load::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		/* TODO */
		/* 
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}*/
		LoadInst *ret = new LoadInst(sym, ident, false, block);
		return ret;
}

void Load::accept(Visitor &v) {
	v.visit(*this); 
}

