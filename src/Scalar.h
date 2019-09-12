#ifndef __SCALAR_H__
#define __SCALAR_H__
#include "Node.h"
#include "Float.h"

class Scalar: public Node {
private:
	string name;
	Node *expr;
public:
	Scalar(const char *n, Node *e) : name(n), expr(e) { }

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
