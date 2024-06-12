
#pragma once

#include "Node.h"

class Float: public Node {
private:
	float number;
public:
	Float(float n, location_t loc): Node(loc), number(n) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tfloat;
	}
};
