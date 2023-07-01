#include "Header.h"

Loop::Loop(Node *stms) : stmts(stms) {
	node_children.reserve(1);
	node_children.push_back(stms);
}

Value *Loop::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	BasicBlock *bodyloop = BasicBlock::Create(global_context, "loop_body", func, 0);
	// alloc instructions inside bodyloop should go to allocblock to prevent repeatedly allocation
	Value *newb = stmts->generate(func, bodyloop, allocblock); 
	BranchInst::Create(bodyloop, bodyloop);
	BranchInst::Create(bodyloop, block);
	return bodyloop;
}

void Loop::accept(Visitor& v) {
	v.visit(*this);
}
