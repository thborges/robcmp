#ifndef __FUNCTIONCALL_H__
#define __FUNCTIONCALL_H__
#include "Node.h"

class FunctionCall: public Node {
private:
	string name;
	FunctionParams *parameters;
public:
	FunctionCall(string names) {
		this->name = name;
	}

	FunctionCall(string names, FunctionParams *fp) {
		this->name = name;
		this->parameters = fp;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
