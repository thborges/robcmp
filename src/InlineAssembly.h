
#pragma once

#include "Node.h"

class InlineAssembly: public Node {
private:
	string assembly;
	string constraints;
public:
	InlineAssembly(const char *_asm, location_t loc): Node(loc), assembly(_asm) { }
	InlineAssembly(const char *_asm, const char *cons, location_t loc): Node(loc), assembly(_asm), constraints(cons) { }
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
