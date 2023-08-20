
#pragma once

#include "Node.h"
#include "Variable.h"
#include "ArrayElements.h"
#include "NamedConst.h"

class ArrayElements;

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
