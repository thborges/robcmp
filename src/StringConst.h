
#pragma once

#include "Node.h"

class StringConst: public Node {
private:
	string str;
public:
	StringConst(const char *s): str(s) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock); 
};
