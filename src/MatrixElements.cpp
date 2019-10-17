#include "Header.h"

MatrixElements::MatrixElements() {};

void MatrixElements::append(MatrixElement& m) {
	element.push_back(m);
};
	
unsigned MatrixElements::getColumnSize() const {
	/*unsigned r = 0;
	unsigned biggest_r = 0;
	for(auto& j : element)
	{
		for (auto& i : j)
			r += i.count;
		if (biggest_r < r)
			biggest_r = r;
		r = 0;
	}	
	return r;*/
};

unsigned MatrixElements::getLineSize() const {
	/*unsigned r = 0;
	for(auto& i : arrays)
		r += 1;
	return r;*/
}
Type *MatrixElements::getMatrixType(Function *func, BasicBlock *block, BasicBlock *allocblock) const {
/*	for(auto& i : arrays){
		if (dynamic_cast<Float*>(arrays[i].value))
			return Type::getFloatTy(global_context);
	}*/
	return Type::getInt16Ty(global_context);
}
