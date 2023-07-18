#ifndef __ARRAY_ELEMENT_H__
#define __ARRAY_ELEMENT_H__

#include "Node.h"

class ArrayElements {
private:
public:
	std::vector<ArrayElement> elements;
	ArrayElements();
	void append(ArrayElement& e);
	
	unsigned getArraySize() const;
	unsigned getStructSize () const;
	unsigned getElementCount (int position) const;
	Node *getStructElement (int position) const;
	LanguageDataType getArrayType(BasicBlock *block, BasicBlock *allocblock) const;
};

#endif

