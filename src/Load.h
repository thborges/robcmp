#pragma once

#include "Node.h"
#include "Identifier.h"

class Load: public Node {
private:
	Identifier ident;
	Variable *leftValue = NULL;
	Node *isymbol = NULL;
	
public:
	Load(const char* i): ident(i) {	}
	Load(Identifier i): ident(i) { }
	Load(Node *n): isymbol(n), ident(n->getName()) { }
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;

	virtual bool isConstExpr() override;

	virtual void setLeftValue(Variable *symbol) override;

	virtual const string getName() const override {
		return ident.getFullName();
	}
};
