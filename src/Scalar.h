
#pragma once

#include "Variable.h"
#include "Visitor.h"

class Scalar: public Variable {
public:
	Scalar(const string& ident, Node *e);

	Scalar(Identifier ident, Node *e);

	Node *expr() {
		return node_children[0];
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return hasQualifier(qconst) && expr()->isConstExpr();
	}

	virtual DataType getDataType() override;

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	friend class SymbolizeTree;
};
