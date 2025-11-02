
#pragma once

#include "semantic/Visitor.h"
#include "ast/LeftValueData.h"

class LoadValue : public Node {
private:
	Value *value;
	bool isVolatile;
public:
	LoadValue(Value *value, DataType dt, bool isVolatile, location_t loc) :
		Node(loc), isVolatile(isVolatile), value(value) {
		this->dt = dt;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
		Type *ty = buildTypes->llvmType(dt);
		return Builder->CreateLoad(ty, value, isVolatile, "loadleftv");
	}
};

class CompoundStore: public Node {
private:
	LeftValueData *leftv;
    Node *expr;
	char op;

public:
	CompoundStore(LeftValueData *lv, char op, Node *e) : 
		Node(lv->value->getLoc()), leftv(lv), expr(e), op(op) {
		node_children.push_back(lv->value);
		node_children.push_back(expr);
	};

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	Node *getExpr() {
		return expr;
	}

	void setExpr(Node *expr) {
		this->expr = expr;
	}

	DataType getLeftDataType() {
		return leftv->value->getDataType();
	}
};
