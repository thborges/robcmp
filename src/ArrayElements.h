#ifndef __ARRAY_ELEMENT_H__
#define __ARRAY_ELEMENT_H__

#include "Node.h"

class ArrayElements {
private:
	std::vector<ArrayElement> elements;
public:
	ArrayElements();
	void append(ArrayElement& e);
	
	unsigned getArraySize() const;
	unsigned getStructSize() const;
	unsigned getElementCount(int position) const;
	Node *getStructElement(int position) const;
	Type *getArrayType(Function *func, BasicBlock *block, BasicBlock *allocblock) const;
};

#endif

