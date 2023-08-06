
#pragma once

#include "Field.h"

class Pointer: public Variable {
private:
    Node *address;
	Structure *structure;
	
public:
	Pointer(const char *name, DataType type, Node *address);

	Pointer(const char *name, DataType type, Node *address, Structure *structure);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};
