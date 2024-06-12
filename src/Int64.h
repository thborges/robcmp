
#pragma once

#include "Node.h"

class Int64: public Node {
private:
	int64_t number;

public:
	Int64(int64_t n, location_t loc): Node(loc), number(n) {}
	
	int64_t getNumber() const { return number; }
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tint64;
	}
};

class UInt64: public Node {
private:
	uint64_t number;

public:
	UInt64(uint64_t n, location_t loc): Node(loc), number(n) {}
	
	uint64_t getNumber() const { return number; }
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tint64u;
	}
};
