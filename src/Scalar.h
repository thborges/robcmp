
#pragma once

#include "Field.h"
#include "Variable.h"

class Scalar: public Variable {
private:
	Node *expr;
	int gepIndex = -1;

public:
	Scalar(const char* ident, Node *e);

	Scalar(Identifier ident, Node *e);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Value* getLLVMValue(Node *stem) override;

	virtual void setGEPIndex(int idx) {
		gepIndex = idx;
	}

	int getGEPIndex() const {
		return gepIndex;
	}

	virtual bool isConstExpr() override {
		return hasQualifier(qconst) && expr->isConstExpr();
	}

	virtual DataType getDataType() override;

};
