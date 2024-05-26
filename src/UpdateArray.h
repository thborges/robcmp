
#pragma once

#include "Node.h"
#include "LoadArray.h"

class UpdateArray: public BaseArrayOper {
protected:
	Node *expr;
public:
	UpdateArray(const string &i, Node *pos, Node *expr);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
