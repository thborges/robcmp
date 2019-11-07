#ifndef __FUNCTIONCALL_H__
#define __FUNCTIONCALL_H__
#include "Node.h"

class FunctionCall: public Node {
private:
	string name;
	ParamsCall *parameters;
public:
	FunctionCall(string names) {
		this->name = name;
	}

	FunctionCall(string names, ParamsCall *pc) {
		this->name = name;
		this->parameters = pc;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
