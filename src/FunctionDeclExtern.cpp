#include "Header.h"

Value *FunctionDeclExtern::generate(Function *, BasicBlock *, BasicBlock *allocblock) {
	auto sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Function/symbol " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", sym);
		return NULL;
	}

	std::vector<Type*> arg_types;
	if (parameters->getNumParams() != 0)
		for (int i = 0; i < parameters->getNumParams(); i++)
			arg_types.push_back(parameters->getParamType(i));
	
	Type *xtype = robTollvmDataType[tipo];
	FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);
	Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, 0, name, mainmodule);
	nfunc->setCallingConv(CallingConv::C);
	tabelasym[allocblock][name] = new RobSymbol(nfunc);

	return nfunc;
}

