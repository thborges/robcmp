
#pragma once

#include "Node.h"

class LoadArray: public Node {
protected:
	string ident;
	Node *position;
	RobSymbol *rsym = NULL;
public:
	LoadArray(const char *i, Node *pos): ident(i), position(pos) {}

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

	virtual LanguageDataType getResultType(BasicBlock *block, BasicBlock *allocblock);

	virtual Node *getLoadIndex(RobSymbol *rsym, BasicBlock *block, BasicBlock *allocblock) {
		return position;
	}

};
