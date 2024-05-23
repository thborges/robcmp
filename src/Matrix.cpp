#include "Matrix.h"
#include "Coercion.h"
#include "Array.h"
#include "BinaryOp.h"
#include "Visitor.h"
#include "BackLLVM.h"
#include "FunctionImpl.h"
#include "NamedConst.h"

Matrix::Matrix(const char *n, MatrixElements *me) : LinearDataStructure(n), melements(me) {
	NamedConst *rows = new NamedConst("rows", getNodeForIntConst(me->getRowCount()));
	NamedConst *cols = new NamedConst("cols", getNodeForIntConst(me->getColumnCount()));
	addChild(rows);
	addChild(cols);
	dt = tarray; //FIXME
}

Node* Matrix::getElementIndex(Node *p1, Node *p2) {
	
	// if constants, validate indexes
	if (p1->isConstExpr()) {
		Value *p1v = p1->generate(NULL, NULL, NULL);
		Constant *c = dyn_cast<Constant>(p1v);
		int64_t v = c->getUniqueInteger().getZExtValue();
		if (v >= rows) {
			yyerrorcpp(string_format("Matrix %s row index (%d) out of bounds.", name.c_str(), v), p1);
		}
	}

	if (p2->isConstExpr()) {
		Value *p1v = p2->generate(NULL, NULL, NULL);
		Constant *c = dyn_cast<Constant>(p1v);
		int64_t v = c->getUniqueInteger().getZExtValue();
		if (v >= cols) {
			yyerrorcpp(string_format("Matrix %s col index (%d) out of bounds.", name.c_str(), v), p2);
		}
	}

	//Generate index of element
	Node *mcols = getNodeForIntConst(melements->getColumnCount());
	return new BinaryOp(new BinaryOp(p1, '*', mcols), '+', p2);
}

Value *Matrix::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	/*
	 * Matrix is generated as an array and accessed latter accordingly!
	 */
	createDataType();

	// Allocate elements. Supported formats:
	// {{1:3}:3, {1:2,2}:2}
	// {{1,1,1},{1,1,1},{1,1,1},{1,1,2},{1,1,2}}
	bool allConst = true;
	vector<Value*> elementValues;
	elementValues.reserve(rows * cols);
	for(MatrixElement *i: getElements()) {
		unsigned elCount = i->count;
		
		for (int j=0; j<elCount; j++) {
			for(ArrayElement *k: i->array->getElements()) {
				Node* elValue = k->value;
				Value *val = elValue->generate(func, block, allocblock);
				if (!val)
					return NULL;
				val = Coercion::Convert(val, matrixType->getElementType(), block, elValue);
				if (!dyn_cast<Constant>(val))
					allConst = false;
				for (int l=0; l < k->count; l++)
					elementValues.push_back(val);
			}
		}
	}

	if (!allConst && (allocblock == NULL || allocblock == global_alloc)) {
		// Load will produce an error informing the usage of other variables 
		// to define a new global variable
		return NULL;
	}

	auto sp = RobDbgInfo.currScope();
	auto funit = RobDbgInfo.currFile();

	//Allocate matrix as a vector.
	//Allocate array.
	if (allocblock == global_alloc) { // when alloc is global
		vector<Constant*> constantValues;
		constantValues.reserve(elementValues.size());
		for(auto &a : elementValues)
			constantValues.push_back(dyn_cast<Constant>(a));
		ArrayRef<Constant*> constantRefs(constantValues);
		GlobalVariable *gv = new GlobalVariable(*mainmodule, matrixType, 
			false, GlobalValue::InternalLinkage, 
			ConstantArray::get(matrixType, constantRefs), name);
		gv->setDSOLocal(true);
		gv->setAlignment(Align(2));
		alloc = gv;

		if (debug_info) {
			auto di_ptr = DBuilder->createPointerType(buildTypes->diType(getElementDt()), 
				buildTypes->bitWidth(currentTarget().pointerType));
			auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
				funit, this->getLineNo(), di_ptr, false);
			gv->addDebugInfo(d);
		}

	} else {
		Builder->SetInsertPoint(allocblock);

		if (getGEPIndex() != -1)
			alloc = getLLVMValue(func);
		else
			alloc = Builder->CreateAlloca(matrixType, dataAddrSpace, 0, name);

		RobDbgInfo.emitLocation(this);
		Builder->SetInsertPoint(block);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		StoreInst *store = NULL;
		for(unsigned index = 0; index < elementValues.size(); index++) {
			Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), index);
			Value* indexList[2] = {zero, idx};
			Value* gep = Builder->CreateGEP(matrixType, alloc, 
				ArrayRef<Value*>(indexList), "elem");
			store = Builder->CreateStore(elementValues[index], gep, false);
		}
	}

	return alloc;
}

void Matrix::accept(Visitor& v) {
	v.visit(*this);
}

void Matrix::createDataType() {
	if (matrixType != NULL)
		return;

	//Get Type of elements in Vector of Elements, and define as I.
	element_dt = melements->getMatrixType();
	Type* I = buildTypes->llvmType(element_dt);
	
	// The matrix size
	rows = melements->getRowCount();
	cols = melements->getColumnCount();
	matrixType = ArrayType::get(I, rows * cols);
}

Type* Matrix::getLLVMType() {
	createDataType();
	return matrixType;
}
