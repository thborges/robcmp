#ifndef __CAPSULE_H__
#define __CAPSULE_H__
#include "Node.h"

class Capsule: public Node {
private:
	Node *node;
public:
	Capsule (Node *n) : node(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return node->generate(func, block, allocblock);
	}
};

#endif
