
#include "Header.h"

If::If(Node *e, Node *tst, Node *est) : expr(e), thenst(tst), elsest(est) {
	node_children.reserve(3);
	node_children.push_back(expr);
	node_children.push_back(thenst);

	if (est != NULL)
		node_children.push_back(elsest);
}

Value *If::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *exprv = expr->generate(func, block, allocblock);

	BasicBlock *thenb = BasicBlock::Create(global_context, "if_then", func, 0);
	Value *thennewb = thenst->generate(func, thenb, allocblock);

	Value *elsenewb = NULL;
	BasicBlock *elseb = BasicBlock::Create(global_context, "if_else", func, 0);
	if (elsest != 0) {
		elsenewb = elsest->generate(func, elseb, allocblock);
	}
	
	BranchInst::Create(thenb, elseb, exprv, block);

	BasicBlock *mergb = BasicBlock::Create(global_context, "if_cont", func, 0);
		
	// identify last then block
	BasicBlock *lastthen = thenb;
	if (thennewb && thennewb->getValueID() == Value::BasicBlockVal)
		lastthen = (BasicBlock*)thennewb;

	// if then block already has a terminator, don't generate branch
	if (!lastthen->getTerminator())
		BranchInst::Create(mergb, lastthen); 
		
	// identify last else block
	BasicBlock *lastelse = elseb;
	if (elsenewb && elsenewb->getValueID() == Value::BasicBlockVal) 
		lastelse = (BasicBlock*)elsenewb;

	// if else block already has a terminator, don't generate branch
	if (!lastelse->getTerminator())
		BranchInst::Create(mergb, lastelse); 

	return mergb;
}

void If::accept(Visitor& v) {
	v.visit(*this);
}

