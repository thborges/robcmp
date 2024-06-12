
#pragma once

#include "Node.h"

class Char: public Node {
private:
	char value;

public:
	Char(char v, location_t loc): Node(loc), value(v) {}

	char getValue() const { return value; }

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	
	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tchar;
	}
};
