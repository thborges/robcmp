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
	return elements.size();
}

BasicDataType ArrayElements::getArrayType(BasicBlock *block, BasicBlock *allocblock) const {
	unsigned intsize = 0;
	unsigned floatsize = 0;
	for(auto& i : elements) {
		BasicDataType dt = i.value->getResultType(block, allocblock);
		if (buildTypes->isIntegerDataType(dt) && intsize < buildTypes->bitWidth(dt))
			intsize = buildTypes->bitWidth(dt);
		
		if (floatsize < 32 && dt == tfloat)
			floatsize = 32;
		else if (floatsize < 64 && dt == tdouble)
			floatsize = 64;
		else if (floatsize < 128 && dt == tldouble)
			floatsize = 128;
	}
	if (intsize == 0 && floatsize == 0) {
		yyerrorcpp("FIXME: vector of non-consts/non-numbers.", NULL);
		return tvoid;
	}
	if (floatsize == 0) {
		switch (intsize) {
			case 1:  return tbool;
			case 8:  return tint8;
			case 16: return tint16;
			case 32: return tint32;
			default: return tint64;
		}
	} else {
		switch (floatsize) {
			case 32: return tfloat;
			case 64: return tdouble;
			default: return tldouble;
		}
	}
}

Node *ArrayElements::getStructElement(int position) const {
	return elements[position].value;
}

unsigned ArrayElements::getElementCount(int position) const {
	return elements[position].count;
}
