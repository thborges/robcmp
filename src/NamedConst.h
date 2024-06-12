
#pragma once

#include "Node.h"

class NamedConst: public NamedNode {
protected:
	Node *value = NULL;
	
public:
	NamedConst(const char *name, location_t loc) : NamedNode(name, loc) {}

	NamedConst(const char *name, Node *value, location_t loc) : NamedNode(name, loc), value(value) {
		dt = value->getDataType();
	}

	virtual Value *getLLVMValue(Node *stem) override {
		return value->generate(NULL, NULL, NULL); //FIXME
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
