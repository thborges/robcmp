#include "Header.h"

While::While(Node *e, Node *stms) : expr(e), stmts(stms) {
	node_children.reserve(2);
	node_children.push_back(e);
	node_children.push_back(stms);
}

Value *While::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	BasicBlock *condwhile = BasicBlock::Create(global_context, "while_cond", func, 0);
	BasicBlock *bodywhile = BasicBlock::Create(global_context, "while_body", func, 0);
	BasicBlock *endwhile = BasicBlock::Create(global_context, "while_end", func, 0);

	// go to condition
	RobDbgInfo.emitLocation(expr);
	Builder->SetInsertPoint(block);
	Builder->CreateBr(condwhile);

	Value *exprv = expr->generate(func, condwhile, allocblock);

	// check condition
	RobDbgInfo.emitLocation(expr);
	Builder->SetInsertPoint(condwhile);
	Builder->CreateCondBr(exprv, bodywhile, endwhile);

	// alloc instructions inside bodywhile should go to allocblock to prevent repeatedly allocation
	Value *newb = stmts->generate(func, bodywhile, allocblock); 

	// identify last while body block
	BasicBlock *endbody = bodywhile;
	if (newb->getValueID() == Value::BasicBlockVal)
		endbody = (BasicBlock*)newb;
	
	// if end block already has a terminator, don't generate branch
	if (!((BasicBlock*)endbody)->getTerminator()) {
		Builder->SetInsertPoint(endbody);
		Builder->CreateBr(condwhile);
	}

	return endwhile;
}

void While::accept(Visitor& v) {
	v.visit(*this);
}

