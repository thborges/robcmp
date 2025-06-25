#include "FlexDependencies.h"
#include "Language_gen_y.hpp"

#include "BinaryOp.h"
#include "FunctionImpl.h"

BinaryOp::BinaryOp(Node *l, int op, Node *r) : Node(l->getLoc()) {
	this->op = op;
	this->addChild(l);
	this->addChild(r);
}

Value *BinaryOp::logical_operator(enum Instruction::BinaryOps op, 
	FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	// The code below implements boolean short-circuit evaluation
	// See https://en.wikipedia.org/wiki/Short-circuit_evaluation

	// left
	BasicBlock *newlblock = block;
	Value *lhs = lhsn()->generateNewBlock(func, &newlblock, allocblock);
	Type *lhsty = lhs->getType();
	
	BasicBlock *fullev = BasicBlock::Create(global_context, "fullev", func->getLLVMFunction());
	BasicBlock *phiblock = BasicBlock::Create(global_context, "phiblock", func->getLLVMFunction());
	PHINode *phi = PHINode::Create(lhsty, 0, "phi", phiblock);
	phi->addIncoming(lhs, newlblock);

	if (op == Instruction::BinaryOps::Or)
		BranchInst::Create(phiblock, fullev, lhs, newlblock);
	else // and
		BranchInst::Create(fullev, phiblock, lhs, newlblock);

	// right
	BasicBlock *newrblock = fullev;
	Value *rhs = rhsn()->generateNewBlock(func, &newrblock, allocblock);
	Builder->SetInsertPoint(newrblock);
	Value *binop = Builder->CreateBinOp(op, lhs, rhs, "logicop");
	BranchInst::Create(phiblock, newrblock);
	phi->addIncoming(binop, newrblock);
	
	if (!lhsty->isIntegerTy() || !(lhsty->getIntegerBitWidth() == 1)) {
		errs() << "Left: " << *lhsty << "\n";
		yyerrorcpp("The left side of the logical expression is not boolean.", this);
	}
	
	Type *rhsty = rhs->getType();
	if (!rhsty->isIntegerTy() || !(rhsty->getIntegerBitWidth() == 1))
		yyerrorcpp("The right side of the logical expression is not boolean.", this);

	return phi;
}

Value *BinaryOp::binary_operator(enum Instruction::BinaryOps opint, 
	enum Instruction::BinaryOps opflt, FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	DataType lty = lhsn()->getDataType();
	DataType rty = rhsn()->getDataType();

	// Generate left and right side
	Value *lhs = lhsn()->generateNewBlock(func, &block, allocblock);
	Value *rhs = rhsn()->generateNewBlock(func, &block, allocblock);

	if (lhs == NULL || rhs == NULL)
		return NULL;

	enum Instruction::BinaryOps llvmop;
	if (buildTypes->isIntegerDataType(lty)) { // it suffices to check one side, operands has been coerced
		if (buildTypes->isUnsignedDataType(lty)) {
			if (opint == Instruction::SDiv)
				opint = Instruction::UDiv;
			else if (opint == Instruction::SRem)
				opint = Instruction::URem;
			else if (opint == Instruction::AShr)
				opint = Instruction::LShr;
		}
		llvmop = opint;
	} else {
		llvmop = opflt;
	}

	Builder->SetInsertPoint(block);
	RobDbgInfo.emitLocation(this);
	return Builder->CreateBinOp(llvmop, lhs, rhs, "binop");
}

DataType BinaryOp::getDataType() {
	return dt;
}

Value *BinaryOp::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	switch (op) {
		case '+' : return binary_operator(Instruction::Add, Instruction::FAdd, func, block, allocblock);
		case '-' : return binary_operator(Instruction::Sub, Instruction::FSub, func, block, allocblock);
		case '*' : return binary_operator(Instruction::Mul, Instruction::FMul, func, block, allocblock);
		case '/' : return binary_operator(Instruction::SDiv, Instruction::FDiv, func, block, allocblock);
		case '%' : return binary_operator(Instruction::SRem, Instruction::SRem, func, block, allocblock);
		case '|' : return binary_operator(Instruction::Or, Instruction::Or, func, block, allocblock);
		case '&' : return binary_operator(Instruction::And, Instruction::And, func, block, allocblock);
		case '^' : return binary_operator(Instruction::Xor, Instruction::Xor, func, block, allocblock);
		case TOK_LSHIFT: return binary_operator(Instruction::Shl, Instruction::Shl, func, block, allocblock);
		case TOK_RSHIFT: return binary_operator(Instruction::AShr, Instruction::AShr, func, block, allocblock);
		case TOK_AND : return logical_operator(BinaryOperator::And, func, block, allocblock);
		case TOK_OR  : return logical_operator(BinaryOperator::Or, func, block, allocblock);
		default: return NULL;
	}
}

bool BinaryOp::isConstExpr() {
	return lhsn()->isConstExpr() && 
		rhsn()->isConstExpr();
}
