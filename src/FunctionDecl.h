#ifndef __FUNCTIONDECL_H__
#define __FUNCTIONDECL_H__
#include "Node.h"

class FunctionDecl: public Node {
private:
	Node *stmts;
	string name;
public:
	FunctionDecl(string name, Node *stmts) {
		this->name = name;
		this->stmts = stmts;
	}
	
	bool isFunctionDecl() {
		return true;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

		/*Value *sym = search_symbol(name);
		if (sym != NULL) {
			yyerrorcpp("Function " + name + " already defined.");
			return NULL;
		}

		BasicBlock *fblock = BasicBlock::Create(global_context, "entry");
		stmts->generate(func, fblock, fblock);

		TerminatorInst *term = fblock->getTerminator();
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
		return nfunc;*/
	}
};

#endif
