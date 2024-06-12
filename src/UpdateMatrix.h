
#pragma once

#include "Node.h"
#include "UpdateArray.h"
#include "LoadMatrix.h"

class UpdateMatrix: public UpdateArray {
public:
	UpdateMatrix(const string &i, Node *p1, Node *p2, Node *expr, location_t loc) :
		UpdateArray(i, p1, expr, loc) {
        this->position2 = p2;
		addChild(p2);
    }

	virtual Node* getElementIndex(Node *symbol) override {
		return LoadMatrix::getElementIndexMatrix(this, symbol);
	}
};
