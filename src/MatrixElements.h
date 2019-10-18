#ifndef __MATRIX_ELEMENTS_H__
#define __MATRIX_ELEMENTS_H__

#include "Node.h"

class MatrixElements {
private:
public:
	std::vector<MatrixElement> elements;
	MatrixElements();
	void append(MatrixElement& m);
	
	unsigned getColumnSize() const;
	unsigned getLineSize() const;
	unsigned getElementCount(int position) const;
	Type *getMatrixType(Function *func, BasicBlock *block, BasicBlock *allocblock) const;
};

#endif

