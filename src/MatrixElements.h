#ifndef __MATRIX_ELEMENTS_H__
#define __MATRIX_ELEMENTS_H__

#include "Node.h"

class MatrixElements {
private:
public:
	MatrixElements();
	std::vector<MatrixElement> elements;
	void append(MatrixElement& m);
	
	unsigned getColumnCount() const;
	unsigned getLineCount() const;
	unsigned getElementCount(int position) const;
	Type *getMatrixType(BasicBlock *block, BasicBlock *allocblock) const;
};

#endif

