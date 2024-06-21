
#pragma once

#include "Variable.h"
#include "Visitor.h"

class Scalar: public Variable {
public:
	Scalar(const string& ident, Node *e);

	Scalar(Identifier ident, Node *e);

	virtual Node *getExpr() override {
		return node_children[0];
	}

	virtual void setExpr(Node *expr) override {
		node_children[0] = expr;
		dt = expr->getDataType();
	} 

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return hasQualifier(qconst) && getExpr()->isConstExpr();
	}

	virtual DataType getDataType() override;

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	friend class SymbolizeTree;
};
