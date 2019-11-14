#include "Header.h"

Value *FunctionDecl::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Function " + name + " already defined.");
		return NULL;
	}

	std::vector<Type*> arg_types;
	if (parameters->getNumParams() != 0)
		for (int i = 0; i < parameters->getNumParams(); i++)
			arg_types.push_back(parameters->getParamType(i));
	FunctionType *ftype = FunctionType::get(tipo, ArrayRef<Type*>(arg_types), false);

	Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, name, mainmodule);

	BasicBlock *fblock = BasicBlock::Create(global_context, "entry");
	unsigned Idx = 0;
	for (auto &Arg : nfunc->args())
	{
		const char *argname = parameters->getParamElement(Idx++);
		Arg.setName(argname);
		tabelasym[fblock][argname] = &Arg;
	}
	nfunc->setCallingConv(CallingConv::C);
	if (tipo->isVoidTy())
		nfunc->setDoesNotReturn();

	stmts->generate(func, fblock, fblock);

	fblock->insertInto(nfunc, 0);

	tabelasym[mainblock][name] = nfunc;
	return nfunc;
}

