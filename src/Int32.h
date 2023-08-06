
#pragma once

#include "Node.h"

class Int32: public Node {
private:
	int number;
	bool IsSigned;
	
public:
	Int32(int n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
	
	int getNumber() const { return number; }

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tint32;
	}
};
