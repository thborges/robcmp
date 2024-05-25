
#pragma once

#include "Node.h"
#include "Variable.h"
#include "ArrayElements.h"

class ArrayElements;

class LinearDataStructure: public Variable {
protected:
	DataType element_dt = BuildTypes::undefinedType;
public:
	LinearDataStructure(const string &n): Variable(n) {}
	virtual Node *getElementIndex(Node *p1, Node *p2) = 0;
	virtual DataType getElementDt() {
		return element_dt;
	}
};

class ParamArray: public LinearDataStructure {
public:
	ParamArray(const string& n, string element_dt_name, location_t loc): LinearDataStructure(n) {
		this->element_dt = buildTypes->getType(element_dt_name, true);
		this->dt = buildTypes->getArrayType(element_dt_name, loc, true);
	}

	ParamArray(const string &n, DataType dt): LinearDataStructure(n) {
		this->dt = dt;
		this->element_dt = buildTypes->getArrayElementType(dt);
	}

	virtual Node *getElementIndex(Node *p1, Node *p2) override {
		return p1;
	}
};

class Array: public LinearDataStructure {
private:
	unsigned int size;
	ArrayElements *elements;
	ArrayType *arrayType = NULL;
	void createDataType();

public:
	Array(const char *n, ArrayElements *aes);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Node *getElementIndex(Node *p1, Node *p2) override;

	std::vector<ArrayElement*> getElements() {
		return elements->getElements();
	}

	virtual void accept(Visitor& v) override;

	virtual Type *getLLVMType() override;

};
