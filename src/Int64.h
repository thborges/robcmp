
#pragma once

#include "Node.h"

class Int64: public Node {
private:
	int number;
	bool IsSigned;

public:
	Int64(int n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
	
	int getNumber() const { return number; }
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tint64;
	}
};
