#pragma once

#include "Node.h"
#include "Identifier.h"
#include "Variable.h"
#include "semantic/Visitor.h"

class LoadBase: public Node {
protected:
	LoadBase *leftValue = NULL;
	Variable *loadSymbol = NULL;
	bool toStore = false;
public:
	LoadBase(location_t loc) : Node(loc) {}

	virtual Variable* getLoadSymbol() {
		return loadSymbol; 
	}

	void setToStore(bool to) {
		LoadBase *lb = this;
		while (lb) {
			lb->toStore = to;
			lb = lb->leftValue;
		}
	}
	
	LoadBase* getLeftValue() {
		return leftValue;
	}
};

class Load: public LoadBase {
private:
	Identifier ident;
	Variable *leftValue = NULL;
	Node *identSymbol = NULL;
	
public:
	Load(const char* i, location_t loc): LoadBase(loc), ident(i, loc) {	}
	Load(Identifier i): LoadBase(i.getLoc()), ident(i.getFullName(), i.getLoc()) { }
	Load(Node *n): LoadBase(n->getLoc()), ident(n->getName(), n->getLoc()) {
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

	static Value* getRecursiveField(Identifier &ident, Node *scope, FunctionImpl *func);
	
	friend class SymbolizeTree;
};
