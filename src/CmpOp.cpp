
#include "CmpOp.h"
#include "FlexDependencies.h"
#include "Language_gen_y.hpp"

CmpOp::CmpOp (Node *l, int op, Node *r, location_t loc): Node(loc) {
	this->op = op;
	this->dt = tbool;
	addChild(l);
	addChild(r);
}

Value *CmpOp::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	CmpInst::Predicate predicate; 

	Value *lexp = lexpn()->generateNewBlock(func, &block, allocblock);
	Value *rexp = rexpn()->generateNewBlock(func, &block, allocblock);

	if (rexp == NULL || lexp == NULL) // can't generate values, error message emitted during generate.
		return ConstantInt::get(Type::getInt1Ty(global_context), 1); // error recovery

	// it suffices to check one side, operands has been coerced
	DataType edt = lexpn()->getDataType();
	bool isFloatCmp = buildTypes->isFloatDataType(edt);
	bool isSignedCmp = buildTypes->isSignedDataType(edt);
	bool isUnsignedCmp = buildTypes->isUnsignedDataType(edt);

	if (buildTypes->isEnum(edt))
		isUnsignedCmp = true;
	
	const string op_error = "Invalid operator for comparison.";

	if (isFloatCmp) {
		switch (op) {
			case EQ_OP: predicate = FCmpInst::FCMP_OEQ; break;
			case NE_OP: predicate = FCmpInst::FCMP_ONE; break;
			case GE_OP: predicate = FCmpInst::FCMP_OGE; break;
			case LE_OP: predicate = FCmpInst::FCMP_OLE; break;
			case GT_OP: predicate = FCmpInst::FCMP_OGT; break;
			case LT_OP: predicate = FCmpInst::FCMP_OLT; break;
			default: yyerrorcpp(op_error, lexpn()); break;
		}
	} else if (isSignedCmp) {
		switch (op) {
			case EQ_OP: predicate = FCmpInst::ICMP_EQ; break;
			case NE_OP: predicate = FCmpInst::ICMP_NE; break;
			case GE_OP: predicate = FCmpInst::ICMP_SGE; break;
			case LE_OP: predicate = FCmpInst::ICMP_SLE; break;
			case GT_OP: predicate = FCmpInst::ICMP_SGT; break;
			case LT_OP: predicate = FCmpInst::ICMP_SLT; break;
			default: yyerrorcpp(op_error, lexpn()); break;
		}
	} else if (isUnsignedCmp) {
		switch (op) {
			case EQ_OP: predicate = FCmpInst::ICMP_EQ; break;
			case NE_OP: predicate = FCmpInst::ICMP_NE; break;
			case GE_OP: predicate = FCmpInst::ICMP_UGE; break;
			case LE_OP: predicate = FCmpInst::ICMP_ULE; break;
			case GT_OP: predicate = FCmpInst::ICMP_UGT; break;
			case LT_OP: predicate = FCmpInst::ICMP_ULT; break;
			default: yyerrorcpp(op_error, lexpn()); break;
		}
	} else
		yyerrorcpp(op_error, lexpn());

	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	if (isFloatCmp)
		return Builder->CreateFCmp(predicate, lexp, rexp, "cmpf");
	else {
		return Builder->CreateICmp(predicate, lexp, rexp, "cmpi");
	}
}
