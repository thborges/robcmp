
#pragma once

#include "Node.h"

class Capsule: public Node {
private:
	Node *node;
public:
	Capsule (Node *n) : node(n) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);
};
