
#pragma once

#include "Node.h"

class Int16: public Node {
private:
	short number;

public:
	Int16(short n, location_t loc): Node(loc), number(n) {}
	
	short getNumber() const { return number; }
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tint16;
	}

};

class UInt16: public Node {
private:
	unsigned short number;

public:
	UInt16(unsigned short n, location_t loc): Node(loc), number(n) {}
	
	unsigned short getNumber() const { return number; }
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tint16u;
	}

};
