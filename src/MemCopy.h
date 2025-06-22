
#pragma once

#include "Node.h"
#include "Variable.h"
#include "semantic/Visitor.h"

class Constructor: public Node {
protected:
	Variable *leftValue = NULL;
	Value *leftGEP = NULL;
public:
	Constructor(location_t l): Node(l) {}

	virtual void setLeftValue(Variable *symbol) override {
		leftValue = symbol;
	}

	virtual void setLeftGEP(Value *gep) {
		leftGEP = gep;
	}
};

class MemCopy: public Constructor {
private:
	Node *expr;

public:
	MemCopy(Node *expr): expr(expr), Constructor(expr->getLoc()) {
		addChild(expr);
		this->expr = expr;
	}
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual const string getName() const override {
		return leftValue->getName();
	}

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	DataType getDataType() override {
		return expr->getDataType();
	}

	friend class SymbolizeTree;
};
