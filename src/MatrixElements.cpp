#include "Header.h"

MatrixElements::MatrixElements() {};

void MatrixElements::append(MatrixElement& m) {
	elements.push_back(m);
};
	
unsigned MatrixElements::getLineCount() const {
	unsigned r = 0;
	for(auto& e : elements)
		r += e.count;
	return r;
};

unsigned MatrixElements::getColumnCount() const {
	unsigned r = 0;
	unsigned biggest_r = 0;
	for(auto& e : elements) {
		for (auto& i : e.array->elements)
			r += i.count;
		if (biggest_r < r)
			biggest_r = r;
		r = 0;
	}	
	return biggest_r;
}

Type *MatrixElements::getMatrixType(BasicBlock *block, BasicBlock *allocblock) const {
	unsigned intsize = 0;
	unsigned floatsize = 0;
	for(auto& j : elements) {
		for (auto& i : j.array->elements) {
			Type *ty = i.value->getLLVMResultType(block, allocblock);
			if (ty->isIntegerTy() && intsize < ty->getIntegerBitWidth())
				intsize = ty->getIntegerBitWidth();
			
			if (floatsize < 32 && ty->isFloatTy())
				floatsize = 32;
			else if (floatsize < 64 && ty->isDoubleTy())
				floatsize = 64;
			else if (floatsize < 128 && ty->isFP128Ty())
				floatsize = 128;
		}
	}
	if (intsize == 0 && floatsize == 0) {
		yyerrorcpp("FIXME: matrix of non-consts.", NULL);
		return NULL;
	}
	if (floatsize == 0) {
		switch (intsize) {
			case 1:  return Type::getInt1Ty(global_context);
			case 8:  return Type::getInt8Ty(global_context);
			case 16: return Type::getInt16Ty(global_context);
			case 32: return Type::getInt32Ty(global_context);
			default: return Type::getInt64Ty(global_context);
		}
	} else {
		switch (floatsize) {
			case 32: return Type::getFloatTy(global_context);
			case 64: return Type::getDoubleTy(global_context);
			default: return Type::getFP128Ty(global_context);
		}
	}
}

unsigned MatrixElements::getElementCount(int position) const {
	return elements[position].count;
}
