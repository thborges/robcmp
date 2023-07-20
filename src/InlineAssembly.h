
#pragma once

#include "Header.h"

class InlineAssembly: public Node {
private:
	string assembly;
public:
	InlineAssembly(const char *a): assembly(a) { }
	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock); 
};
