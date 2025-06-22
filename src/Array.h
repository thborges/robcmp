
#pragma once

#include "Node.h"
#include "Variable.h"
#include "ArrayElements.h"

class ArrayElements;

class ParamArray: public Variable {
protected:
	DataType element_dt = BuildTypes::undefinedType;
	string element_dt_name;
public:
	ParamArray(const string& n, string element_dt_name, location_t loc): Variable(n, loc) {
		this->element_dt_name = element_dt_name;
	}

	ParamArray(const string &n, DataType dt, location_t loc): Variable(n, loc) {
		this->dt = dt;
		this->element_dt = buildTypes->getArrayElementType(dt);
	}

	virtual int getDimensions() {
		return 1;
	}

	DataType getDataType() override {
		if (dt == BuildTypes::undefinedType) {
			element_dt = buildTypes->getType(element_dt_name, true);
			dt = buildTypes->getArrayType(element_dt_name, getLoc(), getDimensions(), true);
		}
		return dt;
	}
};

class Array: public Variable {
protected:
	unsigned int size;
	DataType element_dt = BuildTypes::undefinedType;
	ArrayType *arrayType = NULL;
	ArrayElements *arrayElements;
	virtual void createDataType();

public:
	Array(const string& n, ArrayElements *aes, location_t loc);
	Array(const string& n, location_t loc);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	static Node *getElementIndex(Node *p1, Node *p2, const string& name, 
		int p1size = -1, int p2size = -1, Node *columnNumber = NULL);

	virtual std::vector<ArrayElement*>& getElements() {
		return arrayElements->getElements();
	}

	virtual Node* accept(Visitor& v) override;

	virtual Type *getLLVMType() override;

	virtual DataType getDataType() override;

	virtual DataType getElementDataType() {
		return element_dt;
	}

	virtual int getSize() const {
		return size;
	}

	const ArrayType* getArrayType() {
		return arrayType;
	}
};
