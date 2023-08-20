
#include "If.h"
#include "FunctionImpl.h"
#include "Visitor.h"

If::If(Node *e, vector<Node*> &&tst): expr(e) {
	addChild(expr);
	thenst = new Node(std::move(tst));
	addChild(thenst);
	elsest = NULL;
}

If::If(Node *e, vector<Node*> &&tst, vector<Node*> &&est): If(e, std::move(tst)) {
	elsest = new Node(std::move(est));
	addChild(elsest);
}

Value *If::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *exprv = expr->generate(func, block, allocblock);

	BasicBlock *thenb = BasicBlock::Create(global_context, "if_then", 
		func->getLLVMFunction(), 0);
	Value *thennewb = thenst->generateChildren(func, thenb, allocblock);

	Value *elsenewb = NULL;
	BasicBlock *elseb = BasicBlock::Create(global_context, "if_else", 
		func->getLLVMFunction(), 0);
	if (elsest != 0) {
		elsenewb = elsest->generateChildren(func, elseb, allocblock);
	}
	
	BranchInst::Create(thenb, elseb, exprv, block);

	BasicBlock *mergb = BasicBlock::Create(global_context, "if_cont", 
		func->getLLVMFunction(), 0);
		
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
