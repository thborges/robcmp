#include "Header.h"

LanguageDataType FunctionCall::getResultType(BasicBlock *block, BasicBlock *allocblock) {
	auto symbol = search_symbol(name);
	if (symbol)
		return symbol->dt;
	return tvoid;
}

Value *FunctionCall::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

	auto symbol = search_symbol(name);
	if (symbol == NULL) {
		yyerrorcpp("Function " + name + " not defined.", this);
		return NULL;
	}

	Function *cfunc = dyn_cast<Function>(symbol->value);
	if (cfunc == NULL) {
		yyerrorcpp("Symbol " + name + " is not a function.", this);
		return NULL;
	}

	if (symbol->params->getNumParams() != parameters->getNumParams()) {
		yyerrorcpp(string_format("Function %s has %d argument(s) but was called with %d.",
			name.c_str(), symbol->params->getNumParams(), parameters->getNumParams()), this);
		yyerrorcpp("The function declaration is here.", symbol);
		return NULL;
	}

	vector<Value*> args;
	for (int i = 0; i < parameters->getNumParams(); i++){
		Value *valor = parameters->getParamElement(i)->generate(func, block, allocblock);
		Type *pty = robTollvmDataType[symbol->params->getParamType(i)];
		valor = Coercion::Convert(valor, pty, block, this);
		args.push_back(valor);
	}
	ArrayRef<Value*> argsRef(args);

	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	return Builder->CreateCall(cfunc, argsRef);
}

