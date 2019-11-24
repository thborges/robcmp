#ifndef __FUNCTIONDECL_H__
#define __FUNCTIONDECL_H__
#include "Node.h"

class FunctionDecl: public Node {
private:
	Node *stmts;
	int tipo;
	string name;
	FunctionParams *parameters;
public:
	FunctionDecl(int tipo, string name, FunctionParams *fp, Node *stmts){
		this->tipo = tipo;
		this->stmts = stmts;
		this->name = name;
		this->parameters = fp;
	}
	
	
	bool isFunctionDecl() {
		return true;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif
