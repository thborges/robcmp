#include "Header.h"

OutPort::OutPort (const char *p, Node *e) : port(Int8(atoi(p))) {
	expr = e;
	node_children.reserve(2);
	node_children.push_back(&port);
	node_children.push_back(e);
}

Value *OutPort::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;
		
		args.push_back(port.generate(func, block, allocblock));

		Value *value = expr->generate(func, block, allocblock);
		Value *nvalue = value;
		if (value->getType()->isFloatTy())
			nvalue = new FPToSIInst(value, Type::getInt16Ty(global_context), "trunci", block);

		args.push_back(nvalue);
		//Value *int8v = new TruncInst(value, Type::getInt8Ty(global_context), "", block);
		//args.push_back(int8v);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(analogWrite, argsRef, "", block);
	}
