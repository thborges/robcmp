#pragma once

#include "Node.h"
#include "Load.h"
#include "semantic/Visitor.h"

class ArrayAccess: public LoadBase {
private:
    Node *expr;
	
public:
	ArrayAccess(LoadBase *leftValue, Node *expr):
        LoadBase(leftValue->getLoc()), expr(expr) {
		this->leftValue = leftValue;
		node_children.push_back(leftValue);
		node_children.push_back(expr);
	}
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	Node* getExpr() { return expr; }
};
