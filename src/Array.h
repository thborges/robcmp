
#pragma once

#include "Node.h"
#include "Variable.h"
#include "ArrayElements.h"

class ArrayElements;

/*class LinearDataStructure: public Variable {
protected:
	DataType element_dt = BuildTypes::undefinedType;
public:
	LinearDataStructure(const string &n): Variable(n) {}
	virtual Node *getElementIndex(Node *p1, Node *p2) = 0;
	virtual DataType getElementDt() {
		return element_dt;
	}
};*/

class ParamArray: public Variable {
protected:
	DataType element_dt = BuildTypes::undefinedType;
public:
	ParamArray(const string& n, string element_dt_name, location_t loc): Variable(n) {
		this->element_dt = buildTypes->getType(element_dt_name, true);
		this->dt = buildTypes->getArrayType(element_dt_name, loc, true);
	}

	ParamArray(const string &n, DataType dt): Variable(n) {
		this->dt = dt;
		this->element_dt = buildTypes->getArrayElementType(dt);
	}
};

class Array: public Variable {
private:
	unsigned int size;
	DataType element_dt = BuildTypes::undefinedType;
	ArrayElements *elements;
	ArrayType *arrayType = NULL;
	void createDataType();

public:
	Array(const string& n, ArrayElements *aes);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	static Node *getElementIndex(Node *p1, Node *p2, const string& name, 
		int p1size = -1, int p2size = -1, Node *columnNumber = NULL);

	std::vector<ArrayElement*> getElements() {
		return elements->getElements();
	}

	virtual void accept(Visitor& v) override;

	virtual Type *getLLVMType() override;

	DataType getDataType() override;

	int getSize() const {
		return size;
	}
};
