
#pragma once

#include "Node.h"
#include "Variable.h"
#include "ArrayElements.h"

class ArrayElements;

class NamedConst: public NamedNode {
protected:
	Node *value;
public:
	NamedConst(const char *name, Node *value) : NamedNode(name), value(value) {
		dt = value->getDataType();
	}
	virtual Value *getLLVMValue(Node *stem) override {
		return value->generate(NULL, NULL, NULL); //FIXME
	}
	virtual bool isConstExpr() override {
		return true;
	}
};

class LinearDataStructure: public Variable {
protected:
	DataType element_dt = BuildTypes::undefinedType;
public:
	LinearDataStructure(const char *n): Variable(n) {}
	virtual Node *getElementIndex(Node *p1, Node *p2) = 0;
	virtual DataType getElementDt() {
		return element_dt;
	}
};

class Array: public LinearDataStructure {
private:
	unsigned int size;
	ArrayElements *elements;
public:
	Array(const char *n, ArrayElements *aes);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Node *getElementIndex(Node *p1, Node *p2) override {
		return p1;
	}

	std::vector<ArrayElement*> getElements() {
		return elements->getElements();
	}

	virtual void accept(Visitor& v) override;
};
