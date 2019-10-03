#ifndef __CMPOP_H__
#define __CMPOP_H__
#include "Node.h"

class CmpOp: public Node {
private:
	Node *lexpn;
	Node *rexpn;
	int op;
public:
	CmpOp (Node *l, int op, Node *r);
	int getOperator() const { return op; };
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor& v) override;

};

#endif
