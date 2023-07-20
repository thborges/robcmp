
#include "Header.h"

CmpOp::CmpOp (Node *l, int op, Node *r) : lexpn(l), rexpn(r) {
	this->op = op;
	node_children.reserve(2);
	node_children.push_back(lexpn);
	node_children.push_back(rexpn);
}

Value *CmpOp::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	CmpInst::Predicate predicate; 

	Value *lexp = lexpn->generate(func, block, allocblock);
	Value *rexp = rexpn->generate(func, block, allocblock);

	if (rexp == NULL || lexp == NULL) // can't generate values, error message emitted during generate.
		return ConstantInt::get(Type::getInt1Ty(global_context), 1); // error recover

	Type *tl = lexp->getType();
	Type *tr = rexp->getType();

	bool canCompare = (tl->isIntegerTy() || tl->isFloatingPointTy()) &&
					  (tr->isIntegerTy() || tr->isFloatingPointTy());
	if (!canCompare) {
		yyerrorcpp("Can not compare " + getTypeName(tl) + " and " + 
			getTypeName(tr) + " types.", lexpn);
		return ConstantInt::get(Type::getInt1Ty(global_context), 1); // error recover
	}

	RobDbgInfo.emitLocation(this);

	bool isFloatPointCmp = true;
	if (tl->isFloatingPointTy() && tr->isIntegerTy())
		rexp = Coercion::Convert(rexp, tl, block, rexpn);
	else if (tl->isIntegerTy() && tr->isFloatingPointTy())
		lexp = Coercion::Convert(lexp, tr, block, lexpn);
	else {
		// left and right are integers
		isFloatPointCmp = false;
		unsigned tlbw = tl->getIntegerBitWidth();
		unsigned trbw = tr->getIntegerBitWidth();
		if (tlbw > trbw)
			rexp = Coercion::Convert(rexp, tl, block, rexpn);
		else if (tlbw < trbw)
			lexp = Coercion::Convert(lexp, tr, block, lexpn);
	}

	if (rexp == NULL || lexp == NULL) // coercion not possible, error message during coercion
		return ConstantInt::get(Type::getInt1Ty(global_context), 1); // error recover

	if (op == EQ_OP)	  predicate = isFloatPointCmp ? FCmpInst::FCMP_OEQ : ICmpInst::ICMP_EQ;
	else if (op == NE_OP) predicate = isFloatPointCmp ? FCmpInst::FCMP_UNE : ICmpInst::ICMP_NE;
	else if (op == GE_OP) predicate = isFloatPointCmp ? FCmpInst::FCMP_OGE : ICmpInst::ICMP_SGE;
	else if (op == LE_OP) predicate = isFloatPointCmp ? FCmpInst::FCMP_OLE : ICmpInst::ICMP_SLE;
	else if (op == GT_OP) predicate = isFloatPointCmp ? FCmpInst::FCMP_OGT : ICmpInst::ICMP_SGT;
	else if (op == LT_OP) predicate = isFloatPointCmp ? FCmpInst::FCMP_OLT : ICmpInst::ICMP_SLT;
	else {
		yyerrorcpp("Invalid predicate for comparison.", lexpn);
		return NULL;
	}

	Builder->SetInsertPoint(block);
	if (isFloatPointCmp)
		return Builder->CreateFCmp(predicate, lexp, rexp, "cmpf");
	else {
		return Builder->CreateICmp(predicate, lexp, rexp, "cmpi");
	}
}

void CmpOp::accept(Visitor& v) {
	v.visit(*this);
}
