
#pragma once

#include "Node.h"

class Stmts: public Node {
public:
	Stmts() {};

	Stmts(Node *s) {
		node_children.push_back(s);
	}

	void append(Node *s);

	void prepend(Node *s);

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
};
