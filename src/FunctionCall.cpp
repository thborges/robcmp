#include "Header.h"

Value *FunctionCall::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	auto symbol = search_symbol(name);
	if (symbol == NULL) {
		yyerrorcpp("Function " + name + " not defined.");
		return NULL;
	}

	Function *cfunc = dyn_cast<Function>(symbol->value);
	if (cfunc == NULL) {
		yyerrorcpp("Symbol " + name + " is not a function.");
		return NULL;
	}

	vector<Value*> args;	
	for (int i = 0; i < parameters->getNumParams(); i++){
		Value *valor = parameters->getParamElement(i)->generate(func, block, allocblock);
		args.push_back(valor);
	}
	ArrayRef<Value*> argsRef(args);

	bool isVoidReturn = cfunc->getReturnType()->isVoidTy();
	if (isVoidReturn)
		return CallInst::Create(cfunc, argsRef, "", block);
	else
		return CallInst::Create(cfunc, argsRef, "fc", block);
}

