
#pragma once

#include "Node.h"

class FunctionImpl: public NamedNode {
private:
	Node *stmts;
	BasicDataType tipo;
	FunctionParams *parameters;
	SourceLocation endfunction;
public:
	FunctionImpl(BasicDataType tipo, string name, FunctionParams *fp, Node *stmts, SourceLocation ef) :
		NamedNode(name)
	{
		this->tipo = tipo;
		this->stmts = stmts;
		this->parameters = fp;
		this->endfunction = ef;
		this->node_children.push_back(stmts);
	}
	
	virtual bool isFunctionDecl() override {
		return true;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	DISubroutineType *getFunctionDIType();

	bool validateImplementation(FunctionDecl *decl);

	virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return tipo;
	}
};
