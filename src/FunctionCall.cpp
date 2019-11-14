#include "Header.h"

Value *FunctionCall::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Function *cfunc = (Function*)search_symbol(name, mainblock);
	if (cfunc == NULL) {
		yyerrorcpp("Function " + name + " not defined.");
		return NULL;
	}

	vector<Value*> args;	
	for (int i = 0; i < parameters->getNumParams(); i++){
//		args.push_back(parameters->getParamElement(i));
		args.push_back(search_symbol("a"));
	}
	ArrayRef<Value*> argsRef(args);
	return CallInst::Create(cfunc, argsRef, "", block);
}

