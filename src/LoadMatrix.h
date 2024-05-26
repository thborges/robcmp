#pragma once

#include "Node.h"
#include "Matrix.h"
#include "Array.h"
#include "LoadArray.h"

class LoadMatrix: public LoadArray {
public:
	LoadMatrix(const string &i, Node *p1, Node *p2): LoadArray(i, p1) {
		this->position2 = p2;
		addChild(p2);
	}

	virtual Node* getElementIndex(const Node *symbol) override {
		return getElementIndexMatrix(this, symbol);
	}

	static Node* getElementIndexMatrix(BaseArrayOper *matrix, const Node *symbol) {
		// Get element
		int rows = -1;
		int cols = -1;
		Node *mcols = NULL;
		if (const Matrix *mx = dynamic_cast<const Matrix*>(symbol)) {
			rows = mx->getRows();
			cols = mx->getCols();
			mcols = getNodeForIntConst(cols);
		} else if (const ParamMatrix *pmx = dynamic_cast<const ParamMatrix*>(symbol)) {
			mcols = pmx->getCols();
		}

		return Array::getElementIndex(matrix->getPosition(), matrix->getPosition2(),
			matrix->getIdent(), rows, cols, mcols);
	}
};
