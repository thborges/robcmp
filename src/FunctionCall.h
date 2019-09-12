#ifndef __FUNCTIONCALL_H__
#define __FUNCTIONCALL_H__
#include "Node.h"

class FunctionCall: public Node {
private:
	string name;
public:
	FunctionCall(string name) {
		this->name = name;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
