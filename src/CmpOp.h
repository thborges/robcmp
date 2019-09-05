#ifndef __CMPOP_H__
#define __CMPOP_H__
#include "Node.h"

class CmpOp: public Node {
private:
	Node *lexpn;
	Node *rexpn;
	int op;
public:
	CmpOp (Node *l, int op, Node *r) : lexpn(l), rexpn(r) {
		this->op = op;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		CmpInst::Predicate predicate; 

		Value *lexp = lexpn->generate(func, block, allocblock);
		Value *rexp = rexpn->generate(func, block, allocblock);

		Type *Ty1 = lexp->getType();
		Type *Ty2 = rexp->getType();
		int isFCmp = !Ty1->isIntegerTy() || !Ty2->isIntegerTy();
		if (isFCmp) {
			if (Ty1->isIntegerTy())
				lexp = new SIToFPInst(lexp, Type::getFloatTy(global_context), "", block);
			if (Ty2->isIntegerTy())
				rexp = new SIToFPInst(rexp, Type::getFloatTy(global_context), "", block);
		}

		if (op == EQ_OP)	  predicate = isFCmp ? FCmpInst::FCMP_OEQ : ICmpInst::ICMP_EQ;
		else if (op == NE_OP) predicate = isFCmp ? FCmpInst::FCMP_UNE : ICmpInst::ICMP_NE;
		else if (op == GE_OP) predicate = isFCmp ? FCmpInst::FCMP_OGE : ICmpInst::ICMP_SGE;
		else if (op == LE_OP) predicate = isFCmp ? FCmpInst::FCMP_OLE : ICmpInst::ICMP_SLE;
		else if (op == GT_OP) predicate = isFCmp ? FCmpInst::FCMP_OGT : ICmpInst::ICMP_SGT;
		else if (op == LT_OP) predicate = isFCmp ? FCmpInst::FCMP_OLT : ICmpInst::ICMP_SLT;
		else {
			cerr << "Invalid logical operator" << op << endl;
			return NULL;
		}

		if (isFCmp)
			return new FCmpInst(*block, predicate, lexp, rexp, "cmpf");
		else {
			return new ICmpInst(*block, predicate, lexp, rexp, "cmpi");
		}
	}
};

#endif
