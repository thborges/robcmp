#include "Header.h"

Value *Load::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		auto rsym = search_symbol(ident, allocblock, block);	
		if (rsym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}
		auto sym = rsym->value;
		LoadInst *ret = NULL;
		if (auto *lvalue = dyn_cast<AllocaInst>(sym))
			ret = new LoadInst(lvalue->getAllocatedType(), sym, ident, rsym->isVolatile, block);
		else if (auto *lvalue = dyn_cast<GlobalVariable>(sym))
			ret = new LoadInst(lvalue->getValueType(), sym, ident, rsym->isVolatile, block);
		else if (rsym->pointerType != NULL)
			ret = new LoadInst(rsym->pointerType, sym, ident, rsym->isVolatile, block);
		else {
			printf("ERR: Going to return NULL!\n");
		}
			
		return ret;
}

void Load::accept(Visitor &v) {
	v.visit(*this); 
}

