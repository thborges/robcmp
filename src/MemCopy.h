
#pragma once

#include "Node.h"
#include "Variable.h"

class MemCopy: public Node {
private:
	Node *expr;
	Variable *leftValue = NULL;

public:
	MemCopy(Node *expr) {
		addChild(expr);
		this->expr = expr;
	}

	virtual void setLeftValue(Variable *symbol) override;
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
