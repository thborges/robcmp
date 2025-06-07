
#pragma once

#include "Node.h"
#include "Dispatch.h"

class Program : public Node {
protected:
	Dispatch *dispatch;
	FunctionImpl *funcInitGlobals = NULL;
public:
	Program();
	~Program();

	void declara_auxiliary_c_funcs();

	Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);
	void generate();	
	void generateInjectionSetup(SourceLocation *sl);
	void generateInjectionGlobals(SourceLocation *sl);
	void declareBuiltins();
	void generateBuiltins();
	void doSemanticAnalysis();

	Dispatch* getDispatcher() {
		return dispatch;
	}
};

extern Program* program;
