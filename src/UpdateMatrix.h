
#pragma once

#include "Node.h"

class UpdateMatrix: public UpdateArray {
private:
    Node *position2;
public:
	UpdateMatrix(const char *i, Node *p1, Node *p2, Node *expr) : UpdateArray(i, p1, expr) {
        this->position2 = p2;
    }

	virtual Node *getElementIndex(LinearDataStructure *arr) override {
		return arr->getElementIndex(position, position2);
	}
};
