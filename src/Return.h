
#pragma once

#include "Node.h"

class Return: public Node {
private:
	Node *node;
public:
	Return() {
		node = NULL;
	}

	Return(Node *n) {
		addChild(n);
		this->node = n;
	}
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
