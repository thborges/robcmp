
#pragma once

#include "Node.h"

class UpdateArray: public Node {
protected:
	string ident;
	Node *position;
	Node *expr;
public:
	UpdateArray(const char *i, Node *pos, Node *expr): ident(i), position(pos), expr(expr) {}

	virtual Node *getUpdateIndex(RobSymbol *rsym, BasicBlock *block, BasicBlock *allocblock) {
		return position;
	}

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};
