#include "Header.h"

Value *FunctionCall::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Function *cfunc = (Function*)search_symbol(name, mainblock);
	/* TO-DO */
	
	if (cfunc == NULL) {
		yyerrorcpp("Function " + name + " not defined.");
		return NULL;
	}

	vector<Value*> args;
	args.push_back(search_symbol("a"));
	ArrayRef<Value*> argsRef(args);
	return CallInst::Create(cfunc, argsRef, "", block);
}

