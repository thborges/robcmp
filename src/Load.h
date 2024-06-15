#pragma once

#include "Node.h"
#include "Identifier.h"
#include "Visitor.h"

class Load: public Node {
private:
	Identifier ident;
	Variable *leftValue = NULL;
	Node *identSymbol = NULL;
	
public:
	Load(const char* i, location_t loc): Node(loc), ident(i, loc) {	}
	Load(Identifier i): Node(i.getLoc()), ident(i.getFullName(), i.getLoc()) { }
	Load(Node *n): Node(n->getLoc()), ident(n->getName(), n->getLoc()) {
		identSymbol = n;
	}
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;

	virtual bool isConstExpr() override;

	virtual void setLeftValue(Variable *symbol) override;

	virtual const string getName() const override {
		return ident.getFullName();
	}

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	Node* getIdentSymbol(bool showError = true);
	
	friend class SymbolizeTree;
};
