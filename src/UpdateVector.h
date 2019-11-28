#ifndef __UPDATE_VECTOR_H__
#define __UPDATE_VECTOR_H__
#include "Node.h"

class UpdateVector: public Node {
private:
	string ident;
	Node *position;
	Node *exprs;
public:
	UpdateVector(const char *i, Node *pos, Node *expr): ident(i), position(pos), exprs(expr) {}

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
