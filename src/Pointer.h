
#pragma once

#include "Variable.h"

class Pointer: public Variable {
private:
    Node *address;
	
public:
	Pointer(const char *name, DataType type, Node *address, location_t loc);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	unsigned getFieldStartBit(Node *symbol);
};
