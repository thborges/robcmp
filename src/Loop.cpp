#include "Header.h"

Loop::Loop(Node *stms) : stmts(stms) {
	node_children.reserve(1);
	node_children.push_back(stms);
}

Value *Loop::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	BasicBlock *bodyloop = BasicBlock::Create(global_context, "loop_body", func, 0);
	
	RobDbgInfo.emitLocation(this);

	// go to loop
	Builder->SetInsertPoint(block);
	Builder->CreateBr(bodyloop);

	// alloc instructions inside bodyloop should go to allocblock to prevent repeatedly allocation
	Value *newb = stmts->generate(func, bodyloop, allocblock); 

	// return to loop at end
	Builder->SetInsertPoint(bodyloop);
	Builder->CreateBr(bodyloop);

	BasicBlock *endloop = BasicBlock::Create(global_context, "loop_end", func, 0);
	return endloop;
}

void Loop::accept(Visitor& v) {
	v.visit(*this);
}
