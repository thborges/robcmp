#ifndef __FUNCTIONDECL_H__
#define __FUNCTIONDECL_H__
#include "Node.h"

class FunctionDecl: public Node {
private:
	Node *stmts;
	string name;
	FunctionParams *parameters;
public:
	FunctionDecl(string name, Node *stmts){
		this->stmts = stmts;
		this->name = name;
	}
	
	FunctionDecl(string name, FunctionParams *fp, Node *stmts){
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
