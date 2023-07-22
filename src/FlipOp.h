
#ifndef __FLIPOP_H__
#define __FLIPOP_H__

#include "Node.h"

class FlipOp: public Node {
private:
	Node *value;
public:
	FlipOp(Node *value);

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual void accept(Visitor &v) override;

	virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return value->getResultType(block, allocblock);
	}

	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override;
};

#endif
