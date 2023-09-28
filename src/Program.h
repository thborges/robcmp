
#pragma once

#include "Node.h"

class Program : public Node {
public:
	Program();

	void declara_auxiliary_c_funcs();

	Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);
	void generate();	
	void generateInjectionSetup();
};

extern Program* program;
