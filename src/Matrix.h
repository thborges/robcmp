
#pragma once

#include "Array.h"
#include "MatrixElements.h"
#include "Variable.h"

class ParamMatrix: public ParamArray {
public:
	ParamMatrix(const string& n, string element_dt_name, location_t loc): ParamArray(n, element_dt_name, loc) {}

	virtual int getDimensions() override {
		return 2;
	}
};

class Matrix: public Array {
private:
	MatrixElements *melements;
	unsigned int rows = 0;
	unsigned int cols = 0;
	
protected:
	virtual void createDataType() override;

public:
	Matrix(const char *n, MatrixElements *me, location_t loc);

	std::vector<MatrixElement*> const& getMatrixElements() {
		return melements->getElements();
	}

	Node* accept(Visitor& v) override;

	int getRows() const {
		return rows;
	}

	int getCols() const {
		return cols;
	}
};
