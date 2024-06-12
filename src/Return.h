
#pragma once

#include "Node.h"
#include "Visitor.h"

class Return: public Node {
public:
	Return(location_t loc): Node(loc) {
		dt = tvoid;
	}

	Return(Node *n): Node(n->getLoc()) {
		addChild(n);
	}

	Node *value() {
		if (node_children.empty())
			return NULL;
		return node_children[0];
	}
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	Node* accept(Visitor& v) override {
		return v.visit(*this);
	}
};
