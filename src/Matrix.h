
#pragma once

#include "MatrixElements.h"
#include "Variable.h"

class Matrix: public Variable {
private:
	MatrixElements *melements;
	ArrayType *matrixType = NULL;
	DataType element_dt;
	void createDataType();
	unsigned int rows = 0;
	unsigned int cols = 0;

public:
	Matrix(const char *n, MatrixElements *me);

	virtual Value* generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	std::vector<MatrixElement*> const& getElements() {
		return melements->getElements();
	}

	void accept(Visitor& v) override;

	virtual Type *getLLVMType() override;

	DataType getDataType() override;

	int getRows() const {
		return rows;
	}

	int getCols() const {
		return cols;
	}
};
