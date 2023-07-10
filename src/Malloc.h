#ifndef __MALLOC_H__
#define __MALLOC_H__
#include "Node.h"

class Malloc: public Node {
private:
	Node *expr;
public:
	Malloc(Node *e);
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif

