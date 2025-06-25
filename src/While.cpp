
#include "While.h"
#include "FunctionImpl.h"

While::While(Node *e, location_t loc) : Node(loc), expr(e) {
	addChild(e);
	stmts = NULL;
}

While::While(Node *e, vector<Node*> &&ss, location_t loc) : While(e, loc) {
	stmts = new Node(std::move(ss), loc);
	addChild(stmts);
}

Value *While::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	Function *llvmf = func->getLLVMFunction();
	BasicBlock *condwhile = BasicBlock::Create(global_context, "while_cond", llvmf, 0);

	// go to condition
	RobDbgInfo.emitLocation(expr);
	Builder->SetInsertPoint(block);
	Builder->CreateBr(condwhile);

	BasicBlock *endcondwhile = condwhile;
	Value *exprv = expr->generateNewBlock(func, &endcondwhile, allocblock);

	// check condition
	RobDbgInfo.emitLocation(expr);
	Builder->SetInsertPoint(endcondwhile);

	BasicBlock *bodywhile = BasicBlock::Create(global_context, "while_body", llvmf, 0);
	BasicBlock *endwhile = BasicBlock::Create(global_context, "while_end", llvmf, 0);
	Builder->CreateCondBr(exprv, bodywhile, endwhile);

	// alloc instructions inside bodywhile should go to allocblock to prevent repeatedly allocation
	Value *newb = NULL;
	if (stmts)
		newb = stmts->generateChildren(func, bodywhile, allocblock); 

	// identify last while body block
	BasicBlock *endbody = bodywhile;
	if (newb && newb->getValueID() == Value::BasicBlockVal)
		endbody = (BasicBlock*)newb;
	
	// if end block already has a terminator, don't generate branch
	if (!endbody->getTerminator()) {
		Builder->SetInsertPoint(endbody);
		Builder->CreateBr(condwhile);
	}

	return endwhile;
}
