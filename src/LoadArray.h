
#pragma once

#include "Node.h"
#include "Identifier.h"

class BaseArrayOper: public Node {
protected:
	Identifier ident;
	Node *position;
	Node *position2;
public:
	BaseArrayOper(const string& i, Node *pos, Node *pos2): ident(i), position(pos),
		position2(pos2) {}
	
	virtual Node* getElementIndex(const Node *symbol);

	Node *getPosition() {
		return position;
	}
	
	Node *getPosition2() {
		return position2;
	}

	const string getIdent() {
		return ident.getFullName();
	}
};

class LoadArray: public BaseArrayOper {
public:
	LoadArray(const string& i, Node *pos);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;
};
