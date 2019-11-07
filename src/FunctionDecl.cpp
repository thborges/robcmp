#include "Header.h"

Value *FunctionDecl::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	//TO-DO
	Value *sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Function " + name + " already defined.");
		return NULL;
	}

	BasicBlock *fblock = BasicBlock::Create(global_context, "entry");
	stmts->generate(func, fblock, fblock);

	Instruction *term = fblock->getTerminator();
	Type *ttype = Type::getVoidTy(global_context);
	if (term != NULL && isa<ReturnInst>(term))
		ttype = ((ReturnInst*)term)->getReturnValue()->getType();
	else { // return void at the end
		IRBuilder<> builder(fblock);
		builder.CreateRet(NULL);
	}
	
	std::vector<Type*> arg_types;
	FunctionType *ftype = FunctionType::get(ttype, ArrayRef<Type*>(arg_types), false);

	Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, name, mainmodule);
	nfunc->setCallingConv(CallingConv::C);
	if (ttype->isVoidTy())
		nfunc->setDoesNotReturn();

	fblock->insertInto(nfunc, 0);

	tabelasym[mainblock][name] = nfunc;
	return nfunc;
	//return false; //Avoiding Error - TO REMOVE
}

