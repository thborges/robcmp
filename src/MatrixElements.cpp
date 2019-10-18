#include "Header.h"

MatrixElements::MatrixElements() {};

void MatrixElements::append(MatrixElement& m) {
	elements.push_back(m);
};
	
unsigned MatrixElements::getColumnSize() const {
	unsigned r = 0;
	unsigned biggest_r = 0;
	for(auto& j : elements)
	{
		for (auto& i : j.array->elements)
			r += i.count;
		if (biggest_r < r)
			biggest_r = r;
		r = 0;
	}	
	return biggest_r;
};

unsigned MatrixElements::getLineSize() const {
	unsigned r = 0;
	for(auto& i : elements)
		r += i.count;
	return r;
}

Type *MatrixElements::getMatrixType(Function *func, BasicBlock *block, BasicBlock *allocblock) const {
	for(auto& i : elements){
		for (auto& j : i.array->elements)
			if (dynamic_cast<Float*>(j.value))
				return Type::getFloatTy(global_context);
	}
	return Type::getInt16Ty(global_context);
}

unsigned MatrixElements::getElementCount(int position) const {
	return elements[position].count;
}
