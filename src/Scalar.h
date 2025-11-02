
#pragma once

#include "Load.h"
#include "Variable.h"
#include "semantic/Visitor.h"
#include "ast/LeftValueData.h"

class Scalar: public Variable {
private:
	bool used = false;
	LeftValueData *leftv;

public:
	Scalar(LeftValueData *lv, Node *e);

	Scalar(const string& ident, location_t loc);

	Scalar(const string& ident, Node *e);

	virtual Node *getExpr() override {
		return node_children[0];
	}

	virtual void setExpr(Node *expr) override {
		if (node_children.size() == 0)
			node_children.push_back(expr);
		else 
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

	void setUsed(bool value) {
		used = value;
	}

	bool isUsed() {
		return used;
	}

	Node* getLeftValue() {
		return leftv->value;
	}
	
	friend class SymbolizeTree;
};
