
#pragma once

#include "Node.h"
#include "Array.h"
#include "Identifier.h"

class UpdateArray: public Node {
protected:
	Identifier ident;
	Node *position;
	Node *expr;
public:
	UpdateArray(const char *i, Node *pos, Node *expr);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Node *getElementIndex(LinearDataStructure *arr) {
		return arr->getElementIndex(position, NULL);
	}
};
