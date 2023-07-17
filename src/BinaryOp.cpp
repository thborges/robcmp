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

Value *BinaryOp::logical_operator(enum Instruction::BinaryOps op, 
	Function *func, BasicBlock *block, BasicBlock *allocblock) {

	Value *lhs = lhsn->generate(func, block, allocblock);
	Value *rhs = rhsn->generate(func, block, allocblock);
	return BinaryOperator::Create(op, lhs, rhs, "logicop", block);
}

Value *BinaryOp::binary_operator(enum Instruction::BinaryOps opint, 
	enum Instruction::BinaryOps opflt, Function *func, BasicBlock *block, BasicBlock *allocblock) {

	Value *lhs = lhsn->generate(func, block, allocblock);
	Value *rhs = rhsn->generate(func, block, allocblock);
	if (lhs == NULL || rhs == NULL)
		return NULL;

	Type *Ty1 = lhs->getType();
	Type *Ty2 = rhs->getType();

	enum Instruction::BinaryOps llvmop;

	if (Ty1->isIntegerTy() && Ty2->isIntegerTy()) {
		/*fallback SDiv disabled
		if (opint == Instruction::SDiv) {
			vector<Value*> args;
			args.push_back(lhs);
			args.push_back(rhs);
			ArrayRef<Value*> argsRef(args);
			return CallInst::Create(i16div, argsRef, "", block);
		}*/

		if (opint == Instruction::Shl || opint == Instruction::LShr) {
			// zext the left operator if we know the rside bitwidth
			Constant *c = NULL;
			if (rhsn->isConstExpr(block, allocblock)) {
				Value *v = rhsn->generate(NULL, block, allocblock);
				c = dyn_cast<Constant>(v);
			}
			if (c) {
				int64_t v = c->getUniqueInteger().getZExtValue();
				if (Ty1->getIntegerBitWidth() < v) {
					if (v >= 8 && v <= 15)
						lhs = new ZExtInst(lhs, Type::getInt16Ty(global_context), "zext16", block);
					else if (v >= 16 && v <= 31)
						lhs = new ZExtInst(lhs, Type::getInt32Ty(global_context), "zext32", block);
					else if (v >= 32 && v <= 63)
						lhs = new ZExtInst(lhs, Type::getInt64Ty(global_context), "zext64", block);
					else
						yyerrorcpp("Number of shift bits exceeds the max int precision for left side.", this);
					Ty1 = lhs->getType();
				}
			}
		}

		if (dyn_cast<IntegerType>(Ty1)->getBitWidth() > dyn_cast<IntegerType>(Ty2)->getBitWidth())
			rhs = Coercion::Convert(rhs, Ty1, block, rhsn);
		else
			lhs = Coercion::Convert(lhs, Ty2, block, lhsn);

		llvmop = opint;
	}
	else {
		if (Ty1->isIntegerTy())
			lhs = new SIToFPInst(lhs, Ty2, "castitof", block);
		else if (Ty2->isIntegerTy())
			rhs = new SIToFPInst(rhs, Ty1, "castitof", block);
		llvmop = opflt;
	}

	Constant *c0 = dyn_cast<Constant>(lhs);
	Constant *c1 = dyn_cast<Constant>(rhs);
	if (c0 && c1) {
		switch (getOperator()) {
			case '+': return ConstantExpr::getAdd(c0, c1);
			case '-': return ConstantExpr::getSub(c0, c1);
			case '*': return ConstantExpr::getMul(c0, c1);
			
			case TOK_OR:
			case '|': return ConstantExpr::getOr(c0, c1);
			
			case TOK_AND:
			case '&': return ConstantExpr::getAnd(c0, c1);

			case '^': return ConstantExpr::getXor(c0, c1);
			case TOK_LSHIFT: return ConstantExpr::getShl(c0, c1);
			case TOK_RSHIFT: return ConstantExpr::getLShr(c0, c1);
			default:
				break;
		}
	}
	
	return BinaryOperator::Create(llvmop, lhs, rhs, "binop", block);
}

Type *BinaryOp::getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) {
	Type *lty = lhsn->getLLVMResultType(block, allocblock);
	Type *rty = rhsn->getLLVMResultType(block, allocblock);
	if (lty->isIntegerTy() && rty->isIntegerTy()) {
		if (op == TOK_LSHIFT || op == TOK_RSHIFT) {
			// zext the left operator if we know the rside bitwidth
			Constant *c = NULL;
			if (rhsn->isConstExpr(block, allocblock)) {
				Value *v = rhsn->generate(NULL, block, allocblock);
				c = dyn_cast<Constant>(v);
			}
			if (c) {
				int64_t v = c->getUniqueInteger().getZExtValue();
				if (lty->getIntegerBitWidth() < v) {
					if (v >= 8 && v <= 15)
						return Type::getInt16Ty(global_context);
					else if (v >= 16 && v <= 31)
						return Type::getInt32Ty(global_context);
					else if (v >= 32 && v <= 63)
						return Type::getInt64Ty(global_context);
					else
						return NULL;
				}
			}
		}
		return lty->getIntegerBitWidth() > rty->getIntegerBitWidth() ? lty : rty;
		
	} else {
		if (lty->isIntegerTy())
			return rty;
		else
			return lty;
	}
}

Value *BinaryOp::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
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
		case TOK_RSHIFT: return binary_operator(Instruction::LShr, Instruction::LShr, func, block, allocblock);
		case TOK_AND : return logical_operator(BinaryOperator::And, func, block, allocblock);
		case TOK_OR  : return logical_operator(BinaryOperator::Or, func, block, allocblock);
		default: return NULL;
	}
}

void BinaryOp::accept(Visitor& v) {
	v.visit(*this);
}

bool BinaryOp::isConstExpr(BasicBlock *block, BasicBlock *allocblock) {
	return lhsn->isConstExpr(block, allocblock) && 
		rhsn->isConstExpr(block, allocblock);
}
