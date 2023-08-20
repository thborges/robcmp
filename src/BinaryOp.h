
#pragma once

#include "Node.h"

class BinaryOp: public Node {
private:
	int op;
	Node *lhsn;
	Node *rhsn;

public:
	BinaryOp(Node *l, int op, Node *r);

	Value *logical_operator(enum Instruction::BinaryOps op, 
		FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);

	Value *binary_operator(enum Instruction::BinaryOps opint, 
		enum Instruction::BinaryOps opflt, FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	int getOperator() const { return op; };

	virtual DataType getDataType() override;

	virtual bool isConstExpr() override;
	
};
