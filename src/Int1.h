
#pragma once

#include "Node.h"

class Int1: public Node {
private:
	bool value;

public:
	Int1(bool v, location_t loc): Node(loc), value(v) {}
	bool getValue() const { return value; }
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tbool;
	}

};
