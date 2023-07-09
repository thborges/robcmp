
#pragma once

#include "Node.h"

class UpdateMatrix: public UpdateArray {
private:
    Node *position2;
public:
	UpdateMatrix(const char *i, Node *pos1, Node *pos2, Node *expr) : UpdateArray(i, pos1, expr) {
        this->position2 = pos2;
    } 

	virtual Node *getUpdateIndex(RobSymbol *rsym, BasicBlock *block, BasicBlock *allocblock) override {
		//Generate index of element
		Node *mcols = getNodeForIntConst(rsym->matrixCols);
		return new BinaryOp(new BinaryOp(position, '*', mcols), '+', position2);
	}
};
