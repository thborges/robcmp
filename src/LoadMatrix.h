#pragma once

#include "Node.h"

class LoadMatrix: public LoadArray {
private:
	Node *position2;
public:
	LoadMatrix(const char *i, Node *pos_1, Node *pos_2): LoadArray(i, pos_1) {
		this->position2 = pos_2;
	}

	virtual Node *getLoadIndex(RobSymbol *rsym, BasicBlock *block, BasicBlock *allocblock) override {
		//Generate index of element
		Node *mcols = getNodeForIntConst(rsym->matrixCols);
		return new BinaryOp(new BinaryOp(position, '*', mcols), '+', position2);
	}
};
