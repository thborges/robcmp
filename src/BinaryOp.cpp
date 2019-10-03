#include "Header.h"
#include "Int8.h"

BinaryOp::BinaryOp(Node *l, int op, Node *r) {
	this->lhsn = l;
	this->rhsn = r;
	this->op = op;
	this->node_children.reserve(2);
	this->node_children.push_back(lhsn);
	this->node_children.push_back(rhsn);
}

Instruction *BinaryOp::logical_operator(enum Instruction::BinaryOps op, 
	Function *func, BasicBlock *block, BasicBlock *allocblock) {

	Value *lhs = lhsn->generate(func, block, allocblock);
	Value *rhs = rhsn->generate(func, block, allocblock);
	return BinaryOperator::Create(op, lhs, rhs, "logicop", block);
}

Instruction *BinaryOp::binary_operator(enum Instruction::BinaryOps opint, 
	enum Instruction::BinaryOps opflt, Function *func, BasicBlock *block, BasicBlock *allocblock) {

	Value *lhs = lhsn->generate(func, block, allocblock);
	Value *rhs = rhsn->generate(func, block, allocblock);

	Type *Ty1 = lhs->getType();
	Type *Ty2 = rhs->getType();

	if (Ty1->isIntegerTy() && Ty2->isIntegerTy()) {
		/*fallback SDiv disabled
		if (opint == Instruction::SDiv) {
			vector<Value*> args;
			args.push_back(lhs);
			args.push_back(rhs);
			ArrayRef<Value*> argsRef(args);
			return CallInst::Create(i16div, argsRef, "", block);
		}*/
		return BinaryOperator::Create(opint, lhs, rhs, "", block);
	}
	else {
		Value *flhs = lhs, *frhs = rhs;
		if (Ty1->isIntegerTy())
			flhs = new SIToFPInst(lhs, Type::getFloatTy(global_context), "castitof", block);
			//ADDCOERSION
		if (Ty2->isIntegerTy())
			frhs = new SIToFPInst(rhs, Type::getFloatTy(global_context), "castitof", block);
			//ADDCOERSION
		return BinaryOperator::Create(opflt, flhs, frhs, "binop", block);
	}
}

Value *BinaryOp::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	switch (op) {
		case '+' : return binary_operator(Instruction::Add, Instruction::FAdd, func, block, allocblock);
		case '-' : return binary_operator(Instruction::Sub, Instruction::FSub, func, block, allocblock);
		case '*' : return binary_operator(Instruction::Mul, Instruction::FMul, func, block, allocblock);
		case '/' : return binary_operator(Instruction::SDiv, Instruction::FDiv, func, block, allocblock);
		case '%' : return binary_operator(Instruction::SRem, Instruction::SRem, func, block, allocblock);
		case TOK_AND : return logical_operator(BinaryOperator::And, func, block, allocblock);
		case TOK_OR  : return logical_operator(BinaryOperator::Or, func, block, allocblock);
		default: return NULL;
	}
}

void BinaryOp::accept(Visitor& v) {
	v.visit(*this);
}

