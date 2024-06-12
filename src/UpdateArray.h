
#pragma once

#include "Node.h"
#include "LoadArray.h"
#include "Visitor.h"

class UpdateArray: public BaseArrayOper {
protected:
	DataType element_dt = BuildTypes::undefinedType;
	Node *expr;
public:
	UpdateArray(const string &i, Node *pos, Node *expr, location_t loc);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getElementDataType();

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	void setExpr(Node *n) {
		expr = n;
	}

	Node *getExpr() {
		return expr;
	}
};
