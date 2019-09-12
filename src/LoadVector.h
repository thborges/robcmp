#ifndef __LOAD_H__
#define __LOAD_H__
#include "Node.h"

class Load: public Node {
private:
	string ident;
public:
	Load(const char *i, int pos): ident(i), position(pos) {}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
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
};

#endif
