
#pragma once

#include "Node.h"

class InlineAssembly: public Node {
private:
	string assembly;
public:
	InlineAssembly(const char *a, location_t loc): Node(loc), assembly(a) { }
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
