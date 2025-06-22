
#include "MatrixElements.h"

MatrixElements::MatrixElements(location_t loc): location(loc) {};

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
	set<DataType> types;
	for(auto& j : elements) {
		types.emplace(j->array->getArrayType());
	}
	return ArrayElements::getArrayConstType(types, &location);
}

unsigned MatrixElements::getElementCount(int position) {
	return elements[position]->count;
}
