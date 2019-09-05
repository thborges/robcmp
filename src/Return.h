#ifndef __RETURN_H__
#define __RETURN_H__
#include "Node.h"

class Return: public Node {
private:
	Node *node;
public:
	Return(Node *n) {
		this->node = n;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		IRBuilder<> builder(block);
		Value *ret = node->generate(func, block, allocblock);
		return builder.CreateRet(ret);
	}
};

#endif
