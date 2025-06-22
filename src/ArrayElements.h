
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
	SourceLocation location;
public:
	ArrayElements(location_t loc);
	void append(ArrayElement *e);
	
	unsigned getArraySize();
	unsigned getStructSize ();
	unsigned getElementCount (int position);
	Node *getStructElement (int position);
	DataType getArrayType();
	static DataType getArrayConstType(const set<DataType>& types, SourceLocation *location);
	
	std::vector<ArrayElement*>& getElements() {
		return elements;
	}

	void insertElements(ArrayElements *newElements) {
		elements.insert(elements.end(),
			newElements->elements.begin(), newElements->elements.end());
	}
};
