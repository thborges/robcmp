
#pragma once

#include "Variable.h"

class Scalar: public Variable {
private:
	Node *expr;

public:
	Scalar(const char* ident, Node *e);

	Scalar(Identifier ident, Node *e);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return hasQualifier(qconst) && expr->isConstExpr();
	}

	virtual DataType getDataType() override;

};
