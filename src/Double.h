
#pragma once

#include "Node.h"

class Double: public Node {
private:
	double number;
public:
	Double(double n, location_t loc): Node(loc), number(n) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr() override {
		return true;
	}
	virtual DataType getDataType() override {
		return tdouble;
	}
};
