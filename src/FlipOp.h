
#ifndef __FLIPOP_H__
#define __FLIPOP_H__

#include "Node.h"

class FlipOp: public Node {
private:
	Node *value;

public:
	FlipOp(Node *value);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override {
		return value->getDataType();
	}

	virtual bool isConstExpr() override;
};

#endif
