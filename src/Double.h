#ifndef __DOUBLE_H__
#define __DOUBLE_H__
#include "Node.h"

class Double: public Node {
private:
	float number;
public:
	Double(float n): number(n) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr() override {
		return true;
	}
	virtual DataType getDataType() override {
		return tdouble;
	}
};

#endif
