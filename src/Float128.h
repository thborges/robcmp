#pragma once

#include "Node.h"

class Float128: public Node {
private:
	long double number;
public:
	Float128(long double n, location_t loc): Node(loc), number(n) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	
	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tldouble;
	}
};

