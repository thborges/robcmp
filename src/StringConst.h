
#pragma once

#include "Node.h"

class StringConst: public Node {
private:
	string str;
public:
	StringConst(const char *s, location_t loc): Node(loc), str(s) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock); 
};
