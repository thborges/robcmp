
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

	Type *Ty1 = lexp->getType();
	Type *Ty2 = rexp->getType();
	int isFCmp = !Ty1->isIntegerTy() || !Ty2->isIntegerTy();
	if (isFCmp) {
		if (Ty1->isIntegerTy())
			lexp = Coercion::Convert(lexp, Ty2, block);
			//lexp = new SIToFPInst(lexp, Type::getFloatTy(global_context), "", block);
		if (Ty2->isIntegerTy())
			lexp = Coercion::Convert(lexp, Ty1, block);
			//rexp = new SIToFPInst(rexp, Type::getFloatTy(global_context), "", block);
	}
	else {
		if (dyn_cast<IntegerType>(Ty1)->getBitWidth() > dyn_cast<IntegerType>(Ty2)->getBitWidth())
			rexp = Coercion::Convert(rexp, Ty1, block);
		else
			lexp = Coercion::Convert(lexp, Ty2, block);
	}

	if (op == EQ_OP)	  predicate = isFCmp ? FCmpInst::FCMP_OEQ : ICmpInst::ICMP_EQ;
	else if (op == NE_OP) predicate = isFCmp ? FCmpInst::FCMP_UNE : ICmpInst::ICMP_NE;
	else if (op == GE_OP) predicate = isFCmp ? FCmpInst::FCMP_OGE : ICmpInst::ICMP_SGE;
	else if (op == LE_OP) predicate = isFCmp ? FCmpInst::FCMP_OLE : ICmpInst::ICMP_SLE;
	else if (op == GT_OP) predicate = isFCmp ? FCmpInst::FCMP_OGT : ICmpInst::ICMP_SGT;
	else if (op == LT_OP) predicate = isFCmp ? FCmpInst::FCMP_OLT : ICmpInst::ICMP_SLT;
	else {
		/* TO_DO */
		/*
		cerr << "Invalid logical operator" << op << endl;
		return NULL;
		*/
	}

	if (isFCmp)
		return new FCmpInst(*block, predicate, lexp, rexp, "cmpf");
	else {
		return new ICmpInst(*block, predicate, lexp, rexp, "cmpi");
	}
}

void CmpOp::accept(Visitor& v) {
	v.visit(*this);
}
