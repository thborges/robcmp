#include "Header.h"

Value *InPort::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	vector<Value*> args;
		
	Int8 prt(atoi(port.c_str()));
	args.push_back(prt.generate(func, block, allocblock));
		
	ArrayRef<Value*> argsRef(args);
	return CallInst::Create(analogRead, argsRef, "", block);
}

