
#pragma once

#include "Node.h"

class Int8: public Node {
private:
	int8_t number;
	bool IsSigned;

public:
	Int8(int8_t n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}

	int8_t getNumber() const { return number; }

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	
	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tint8;
	}
};
