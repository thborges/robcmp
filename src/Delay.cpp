#include "Header.h"

Delay::Delay(Node *mseg) : ms(mseg) {
	node_children.reserve(1);
	node_children.push_back(ms);
}

Value *Delay::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *msv = ms->generate(func, block, allocblock);
	Value *msv32 = new SExtInst(msv, Type::getInt32Ty(global_context), "conv", block);

	vector<Value*> args;
	args.push_back(msv32);
	ArrayRef<Value*> argsRef(args);
	return CallInst::Create(delay, argsRef, "", block);
}

void Delay::accept(Visitor& v) {
	v.visit(*this);
}

