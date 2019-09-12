
#include "Header.h"

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
		
	if (thennewb->getValueID() == Value::BasicBlockVal) 
		BranchInst::Create(mergb, (BasicBlock*)thennewb);
	else
		BranchInst::Create(mergb, thenb);
		
	if (elsenewb && elsenewb->getValueID() == Value::BasicBlockVal) 
		BranchInst::Create(mergb, (BasicBlock*)elsenewb);
	else
		BranchInst::Create(mergb, elseb);

	return mergb;
}
