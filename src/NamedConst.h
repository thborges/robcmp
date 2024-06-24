
#pragma once

#include "Node.h"

class NamedConst: public NamedNode {
protected:
	Node *value = NULL;
	
public:
	NamedConst(const char *name, location_t loc) : NamedNode(name, loc) {}

	NamedConst(const char *name, Node *v, location_t loc) : NamedNode(name, loc), value(v) {
		dt = value->getDataType();
	}

	Value* generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
		return value->generate(NULL, NULL, NULL);
	}

	virtual Value *getLLVMValue(Node *stem) override {
		return value->generate(NULL, NULL, NULL);
	}

	virtual bool isConstExpr() override {
		return true;
	}

	virtual void setValue(Node *n) {
		value = n;
		dt = value->getDataType();
	}

	Node *getValue() {
		return value;
	}
};
