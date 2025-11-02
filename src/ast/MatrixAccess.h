#pragma once

#include "Node.h"
#include "Load.h"
#include "semantic/Visitor.h"

class MatrixAccess: public LoadBase {
private:
    Node *expr1, *expr2;
	
public:
	MatrixAccess(LoadBase *leftValue, Node *expr1, Node *expr2):
        LoadBase(leftValue->getLoc()), expr1(expr1), expr2(expr2) {
		this->leftValue = leftValue;
		node_children.push_back(leftValue);
		node_children.push_back(expr1);
		node_children.push_back(expr2);
	}
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}
};
