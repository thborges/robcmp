#ifndef __ARRAY_ELEMENT_H__
#define __ARRAY_ELEMENT_H__

#include "Node.h"

class ArrayElements {
private:
	std::vector<ArrayElement> elements;
public:
	ArrayElements() {};
	void append(ArrayElement& e) {
		elements.push_back(e);
	};
	unsigned getArraySize() const {
		unsigned r = 0;
		for(auto& i : elements)
			r += i.count;
		return r;
	};
	Type *getArrayType() const {
		// TODO:
		return Type::getInt8Ty(global_context);
	}
};

#endif

