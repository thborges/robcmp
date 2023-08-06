
#pragma once

#include "Node.h"

class Int8: public Node {
private:
	char number;
	bool IsSigned;

public:
	Int8(char n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
	char getNumber() const { return number; }
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tint8;
	}
};
