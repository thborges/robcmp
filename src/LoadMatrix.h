#pragma once

#include "Node.h"
#include "Matrix.h"
#include "Array.h"
#include "LoadArray.h"
#include "Load.h"

class LoadMatrix: public LoadArray {
public:
	LoadMatrix(const string &i, Node *p1, Node *p2): LoadArray(i, p1) {
		this->position2 = p2;
		addChild(p2);
	}

	virtual Node* getElementIndex(Node *symbol) override {
		return getElementIndexMatrix(this, symbol);
	}

	static Node* getElementIndexMatrix(BaseArrayOper *matrix, Node *symbol) {
		// Get element
		int rows = -1;
		int cols = -1;
		Node *mcols = NULL;
		if (const Matrix *mx = dynamic_cast<const Matrix*>(symbol)) {
			rows = mx->getRows();
			cols = mx->getCols();
			mcols = getNodeForIntConst(cols);
		} else if (Node *s = symbol->findSymbol("cols", false)) {
			mcols = new Load(s);
			mcols->setScope(symbol);
		}

		assert(mcols && "Missing the number of columns to compute the matrix element index.");

		return Array::getElementIndex(matrix->getPosition(), matrix->getPosition2(),
			matrix->getIdent(), rows, cols, mcols);
	}
};
