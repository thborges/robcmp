
#include "InPort.h"

Value *InPort::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	/*vector<Value*> args;
		
	Int8 prt(atoi(port.c_str()));
	Value *v = prt.generate(func, block, allocblock);
	//v = Coercion::Convert(v, Type::getInt8Ty(global_context));
	args.push_back(v);
		
	ArrayRef<Value*> argsRef(args);
	return CallInst::Create(analogRead, argsRef, "", block);*/
	
	//TODO: Implement a new way of reading ports
	return NULL;
}

