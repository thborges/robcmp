
#pragma once

#include "Node.h"

class ArrayElement {
public:
	Node *value;
	unsigned count;
	ArrayElement(Node *value, unsigned count): value(value), count(count) {}
};

class ArrayElements {
private:
	std::vector<ArrayElement*> elements;
public:
	ArrayElements();
	void append(ArrayElement *e);
	
	unsigned getArraySize();
	unsigned getStructSize ();
	unsigned getElementCount (int position);
	Node *getStructElement (int position);
	DataType getArrayType();
	
	std::vector<ArrayElement*> const& getElements() {
		return elements;
	}
};
