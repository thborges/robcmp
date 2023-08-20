
#include "MatrixElements.h"

MatrixElements::MatrixElements() {};

void MatrixElements::append(MatrixElement *m) {
	elements.push_back(m);
};
	
unsigned MatrixElements::getRowCount() {
	unsigned r = 0;
	for(auto& e : elements)
		r += e->count;
	return r;
};

unsigned MatrixElements::getColumnCount() {
	unsigned r = 0;
	unsigned biggest_r = 0;
	for(auto& e : elements) {
		for (auto& i : e->array->getElements())
			r += i->count;
		if (biggest_r < r)
			biggest_r = r;
		r = 0;
	}	
	return biggest_r;
}

DataType MatrixElements::getMatrixType() {
	unsigned intsize = 0;
	unsigned floatsize = 0;
	for(auto& j : elements) {
		for (auto& i : j->array->getElements()) {
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

unsigned MatrixElements::getElementCount(int position) {
	return elements[position]->count;
}
