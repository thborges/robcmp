
#pragma once

#include "Node.h"
#include "Variable.h"
#include "Visitor.h"

class MemCopy: public Node {
private:
	Node *expr;
	Variable *leftValue = NULL;

public:
	MemCopy(Node *expr): Node(expr->getLoc()) {
		addChild(expr);
		this->expr = expr;
	}

	virtual void setLeftValue(Variable *symbol) override;
	
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
