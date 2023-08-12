
#pragma once

#include "MatrixElements.h"
#include "Array.h"

class Matrix: public LinearDataStructure {
private:
	MatrixElements *melements;
	ArrayType *matrixType = NULL;
	void createDataType();
	unsigned int lines = 0;
	unsigned int cols = 0;

public:
	Matrix(const char *n, MatrixElements *me);

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual Node *getElementIndex(Node *p1, Node *p2) override;

	std::vector<MatrixElement*> const& getElements() {
		return melements->getElements();
	}

	void accept(Visitor& v) override;

	virtual Type *getLLVMType() override;
};
