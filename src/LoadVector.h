#ifndef __LOAD_VECTOR_H__
#define __LOAD_VECTOR_H__
#include "Node.h"

class LoadVector: public Node {
private:
	string ident;
	Node *position;
public:
	LoadVector(const char *i, Node *pos): ident(i), position(pos) {}

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
