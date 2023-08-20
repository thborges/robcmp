
#pragma once

#include "Node.h"
#include "Array.h"
#include "Identifier.h"

class LoadArray: public Node {
protected:
	Identifier ident;
	Node *position;
	LinearDataStructure *rsym = NULL;
public:
	LoadArray(const char *i, Node *pos);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Node *getElementIndex(LinearDataStructure *arr) {
		return arr->getElementIndex(position, NULL);
	}

	virtual DataType getDataType() override;
};
