#include "Matrix.h"
#include "Array.h"
#include "BackLLVM.h"
#include "FunctionImpl.h"
#include "NamedConst.h"
#include "semantic/Visitor.h"

Matrix::Matrix(const char *n, MatrixElements *me, location_t loc) : Array(n, loc), melements(me) {
	NamedConst *rows = new NamedConst("rows", getNodeForUIntConst(me->getRowCount(), this->getLoc()));
	NamedConst *cols = new NamedConst("cols", getNodeForUIntConst(me->getColumnCount(), this->getLoc()));
	addChild(rows);
	addSymbol("rows", rows);
	addChild(cols);
	addSymbol("cols", cols);

	// fill arrayElements with matrix elements copy
	for(auto &melem : melements->getElements()) {
		for(int repeat = 0; repeat < melem->count; repeat++)
		arrayElements->insertElements(melem->array);
	}
}

Node* Matrix::accept(Visitor& v) {
	return v.visit(*this);
}

void Matrix::createDataType() {
	if (arrayType != NULL)
		return;

	//Get Type of elements in Vector of Elements, and define as I.
	element_dt = melements->getMatrixType();
	dt = buildTypes->getArrayType(buildTypes->name(element_dt),
		this->getLoc(), 2, true);
	Type* I = buildTypes->llvmType(element_dt);
	if (buildTypes->isComplex(element_dt)) {
		// in rob, all matrices of user types (complex types)
		// are matrices of references
		I = PointerType::getUnqual(I);
	}

	// The matrix type and size
	rows = melements->getRowCount();
	cols = melements->getColumnCount();
	size = rows * cols;
	arrayType = ArrayType::get(I, size);
}
