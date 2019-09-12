#ifndef __CMPOP_H__
#define __CMPOP_H__
#include "Node.h"

class CmpOp: public Node {
private:
	Node *lexpn;
	Node *rexpn;
	int op;
public:
	CmpOp (Node *l, int op, Node *r) : lexpn(l), rexpn(r) {
		this->op = op;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif
