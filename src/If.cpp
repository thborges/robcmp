
#include "If.h"
#include "FunctionImpl.h"
#include "semantic/Visitor.h"

If::If(Node *e, vector<Node*> &&tst, location_t loc): Node(loc), expr(e) {
	addChild(expr);
	thenst = new Node(std::move(tst), loc);
	addChild(thenst);
	elsest = NULL;
}

If::If(Node *e, vector<Node*> &&tst, vector<Node*> &&est, location_t loc): If(e, std::move(tst), loc) {
	elsest = new Node(std::move(est), loc);
	addChild(elsest);
}

Value *If::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	BasicBlock *newblock = block;
	Value *exprv = expr->generateNewBlock(func, &newblock, allocblock);
	if (!exprv) {
		// This occurs when loading a var still not defined, so
		// we let it be False to recovery from the error
		exprv = ConstantInt::get(Type::getInt1Ty(global_context), 0);
	}
	
	BasicBlock *thenb = BasicBlock::Create(global_context, "if_then", 
		func->getLLVMFunction(), 0);
	Value *thennewb = thenst->generateChildren(func, thenb, allocblock);

	Value *elsenewb = NULL;
	BasicBlock *elseb = BasicBlock::Create(global_context, "if_else", 
		func->getLLVMFunction(), 0);
	if (elsest != 0) {
		elsenewb = elsest->generateChildren(func, elseb, allocblock);
	}

	BranchInst::Create(thenb, elseb, exprv, newblock);

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

Node* If::accept(Visitor& v) {
	return v.visit(*this);
} 
