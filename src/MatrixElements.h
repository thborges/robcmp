
#pragma once

#include "Node.h"
#include "ArrayElements.h"

class MatrixElement {
public:
	ArrayElements *array;
	unsigned count;
	MatrixElement(ArrayElements *array, unsigned count): array(array), count(count) {}
};

class MatrixElements {
private:
	std::vector<MatrixElement*> elements;
public:
	MatrixElements();
	void append(MatrixElement *m);
	
	unsigned getColumnCount();
	unsigned getLineCount();
	unsigned getElementCount(int position);
	DataType getMatrixType(FunctionImpl *func);
	
	std::vector<MatrixElement*> const& getElements() {
		return elements;
	}
};
