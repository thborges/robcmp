#include "FlexDependencies.h"
#include "Language_gen_y.hpp"

#include "BinaryOp.h"
#include "Coercion.h"

BinaryOp::BinaryOp(Node *l, int op, Node *r) {
	this->lhsn = l;
	this->rhsn = r;
	this->op = op;
	this->addChild(lhsn);
	this->addChild(rhsn);
}

Value *BinaryOp::logical_operator(enum Instruction::BinaryOps op, 
	FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	Value *lhs = lhsn->generate(func, block, allocblock);
	Value *rhs = rhsn->generate(func, block, allocblock);

	Type *lhsty = lhs->getType();
	Type *rhsty = rhs->getType();
	if (!lhsty->isIntegerTy() || !(lhsty->getIntegerBitWidth() == 1))
		yyerrorcpp("The left side of the logical expression is not boolean.", this);
	
	if (!rhsty->isIntegerTy() || !(rhsty->getIntegerBitWidth() == 1))
		yyerrorcpp("The right side of the logical expression is not boolean.", this);

	Builder->SetInsertPoint(block);
	return Builder->CreateBinOp(op, lhs, rhs, "logicop");
}

Value *BinaryOp::binary_operator(enum Instruction::BinaryOps opint, 
	enum Instruction::BinaryOps opflt, FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	Value *lhs = lhsn->generate(func, block, allocblock);
	Value *rhs = rhsn->generate(func, block, allocblock);
	if (lhs == NULL || rhs == NULL)
		return NULL;

	Type *Ty1 = lhs->getType();
	Type *Ty2 = rhs->getType();

	enum Instruction::BinaryOps llvmop;

	Builder->SetInsertPoint(block);

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
			if (rhsn->isConstExpr()) {
				Value *v = rhsn->generate(NULL, block, allocblock);
				c = dyn_cast<Constant>(v);
			}
			if (c) {
				RobDbgInfo.emitLocation(this);
				int64_t v = c->getUniqueInteger().getZExtValue();
				if (Ty1->getIntegerBitWidth() < v) {
					if (v >= 8 && v <= 15)
						lhs = Builder->CreateZExt(lhs, Type::getInt16Ty(global_context), "zext16");
					else if (v >= 16 && v <= 31)
						lhs = Builder->CreateZExt(lhs, Type::getInt32Ty(global_context), "zext32");
					else if (v >= 32 && v <= 63)
						lhs = Builder->CreateZExt(lhs, Type::getInt64Ty(global_context), "zext64");
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
		RobDbgInfo.emitLocation(this);
		if (Ty1->isIntegerTy())
			lhs = Builder->CreateSIToFP(lhs, Ty2, "castitof");
		else if (Ty2->isIntegerTy())
			rhs = Builder->CreateSIToFP(rhs, Ty1, "castitof");
		llvmop = opflt;
	}

	RobDbgInfo.emitLocation(this);
	return Builder->CreateBinOp(llvmop, lhs, rhs, "binop");
}

DataType BinaryOp::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		DataType lty = lhsn->getDataType();
		DataType rty = rhsn->getDataType();
		if (buildTypes->isIntegerDataType(lty) && buildTypes->isIntegerDataType(rty)) {
			if (op == TOK_LSHIFT || op == TOK_RSHIFT) {
				// zext the left operator if we know the rside bitwidth
				Constant *c = NULL;
				if (rhsn->isConstExpr()) {
					Value *v = rhsn->generate(NULL, NULL, NULL);
					c = dyn_cast<Constant>(v);
				}
				if (c) {
					int64_t v = c->getUniqueInteger().getZExtValue();
					if (buildTypes->bitWidth(lty) < v) {
						if (v >= 8 && v <= 15)
							dt = tint16;
						else if (v >= 16 && v <= 31)
							dt = tint32;
						else if (v >= 32 && v <= 63)
							dt = tint64;
						else
							dt = tvoid;
					}
				}
			}
			dt = buildTypes->bitWidth(lty) > buildTypes->bitWidth(rty) ? lty : rty;
			
		} else {
			if (buildTypes->isIntegerDataType(lty))
				dt = rty;
			else
				dt = lty;
		}
	}
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
		case TOK_RSHIFT: return binary_operator(Instruction::LShr, Instruction::LShr, func, block, allocblock);
		case TOK_AND : return logical_operator(BinaryOperator::And, func, block, allocblock);
		case TOK_OR  : return logical_operator(BinaryOperator::Or, func, block, allocblock);
		default: return NULL;
	}
}

bool BinaryOp::isConstExpr() {
	return lhsn->isConstExpr() && 
		rhsn->isConstExpr();
}
