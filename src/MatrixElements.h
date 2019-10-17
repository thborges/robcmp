#ifndef __MATRIX_ELEMENTS_H__
#define __MATRIX_ELEMENTS_H__

#include "Node.h"

class MatrixElements {
private:
	std::vector<MatrixElement> element;
public:
	MatrixElements();
	void append(MatrixElement& m);
	
	unsigned getColumnSize() const;
	unsigned getLineSize() const;
	Type *getMatrixType(Function *func, BasicBlock *block, BasicBlock *allocblock) const;
};

#endif

