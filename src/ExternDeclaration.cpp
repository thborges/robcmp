#include "Header.h"

Value *ExternDeclaration::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
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

    Function *function = Function::Create(ftype, GlobalValue::ExternalLinkage, name.c_str(), mainmodule);
	tabelasym[allocblock][name] = new RobSymbol(function);
    return function;
}

