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

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif
