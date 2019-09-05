#ifndef __DELAY_H__
#define __DELAY_H__
#include "Node.h"
#include "Int32.h"

class Delay: public Node {
private:
	Node *ms;
public:
	Delay (Node *mseg) : ms(mseg) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *msv = ms->generate(func, block, allocblock);
		Value *msv32 = new SExtInst(msv, Type::getInt32Ty(global_context), "conv", block);

		vector<Value*> args;
		args.push_back(msv32);
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(delay, argsRef, "", block);
	}
};

#endif
