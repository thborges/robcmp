#pragma once

#include "Node.h"
#include "Array.h"
#include "LoadArray.h"

class LoadMatrix: public LoadArray {
private:
	Node *position2;
public:
	LoadMatrix(const char *i, Node *p1, Node *p2): LoadArray(i, p1) {
		this->position2 = p2;
		addChild(p2);
	}

	virtual Node *getElementIndex(LinearDataStructure *arr) override {
		return arr->getElementIndex(position, position2);
	}

};
