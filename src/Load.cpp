#include "Header.h"

Value *Load::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}
		LoadInst *ret = NULL;
		if (auto *lvalue = dyn_cast<AllocaInst>(sym))
			ret = new LoadInst(lvalue->getAllocatedType(), sym, ident, false, block);
		else if (auto *lvalue = dyn_cast<GlobalVariable>(sym)) {
			ret = new LoadInst(lvalue->getValueType(), sym, ident, false, block);
		} else {
			printf("ERR: Going to return NULL!\n");
		}
			
		return ret;
}

void Load::accept(Visitor &v) {
	v.visit(*this); 
}

