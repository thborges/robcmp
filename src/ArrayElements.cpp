#include "Header.h"

ArrayElements::ArrayElements() {};

void ArrayElements::append(ArrayElement& e) {
	elements.push_back(e);
};
	
unsigned ArrayElements::getArraySize() const {
	unsigned r = 0;
	for(auto& i : elements)
		r += i.count;
	return r;
};

unsigned ArrayElements::getStructSize() const {
	unsigned r = 0;
	for (auto& i : elements)
		r += 1;
	return r;
}

Type *ArrayElements::getArrayType() const {
	// TODO:	
	for(auto& i : elements){
	//Generate Problem
		if (dynamic_cast<Float*>(i.value))
			return Type::getFloatTy(global_context);
	}
	return Type::getInt16Ty(global_context);
}

Node *ArrayElements::getStructElement(int position) const {
	return elements[position].value;
}

unsigned ArrayElements::getElementCount(int position) const {
	return elements[position].count;
}
