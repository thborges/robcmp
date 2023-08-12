
#include "ArrayElements.h"

ArrayElements::ArrayElements() {};

void ArrayElements::append(ArrayElement *e) {
	elements.push_back(e);
};
	
unsigned ArrayElements::getArraySize() {
	unsigned r = 0;
	for(auto& i : elements)
		r += i->count;
	return r;
};

unsigned ArrayElements::getStructSize() {
	return elements.size();
}

DataType ArrayElements::getArrayType() {
	unsigned intsize = 0;
	unsigned floatsize = 0;
	for(auto& i : elements) {
		DataType dt = i->value->getDataType();
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

Node *ArrayElements::getStructElement(int position) {
	return elements[position]->value;
}

unsigned ArrayElements::getElementCount(int position) {
	return elements[position]->count;
}
