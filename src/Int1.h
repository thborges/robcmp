
#pragma once

#include "Node.h"

class Int1: public Node {
private:
	char number;

public:
	Int1(char n): number(n) {}
	char getNumber() const { return number; }
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tbool;
	}

};
