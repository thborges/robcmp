#ifndef __BINARYOP_H__
#define __BINARYOP_H__
#include "Node.h"

class BinaryOp: public Node {
private:
	int op;
	Node *lhsn;
	Node *rhsn;
public:
	BinaryOp(Node *l, int op, Node *r);

	Value *logical_operator(enum Instruction::BinaryOps op, 
		Function *func, BasicBlock *block, BasicBlock *allocblock);

	Value *binary_operator(enum Instruction::BinaryOps opint, 
		enum Instruction::BinaryOps opflt, Function *func, BasicBlock *block, BasicBlock *allocblock);

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual void accept(Visitor &v) override;

	int getOperator() const { return op; };

	virtual Type *getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override;
};

#endif
