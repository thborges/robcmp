#include "Matrix.h"
#include "Array.h"
#include "BackLLVM.h"
#include "FunctionImpl.h"
#include "NamedConst.h"
#include "semantic/Visitor.h"

Matrix::Matrix(const char *n, MatrixElements *me, location_t loc) : Variable(n, loc), melements(me) {
	NamedConst *rows = new NamedConst("rows", getNodeForUIntConst(me->getRowCount(), this->getLoc()));
	NamedConst *cols = new NamedConst("cols", getNodeForUIntConst(me->getColumnCount(), this->getLoc()));
	addChild(rows);
	addSymbol("rows", rows);
	addChild(cols);
	addSymbol("cols", cols);
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

	//Allocate matrix as an array.
	if (allocblock == global_alloc) { // when alloc is global
		vector<Constant*> constantValues;
		constantValues.reserve(elementValues.size());
		for(auto &a : elementValues)
			constantValues.push_back(dyn_cast<Constant>(a));
		ArrayRef<Constant*> constantRefs(constantValues);
		GlobalVariable *gv = new GlobalVariable(*mainmodule, matrixType, 
			false, GlobalValue::InternalLinkage, 
			ConstantArray::get(matrixType, constantRefs), name);
		alloc = gv;

		if (debug_info) {
			auto di_ptr = DBuilder->createPointerType(buildTypes->diType(element_dt), 
				buildTypes->bitWidth(currentTarget().pointerType));
			auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
				funit, this->getLineNo(), di_ptr, false);
			gv->addDebugInfo(d);
		}

	} else {
		Builder->SetInsertPoint(allocblock);

		if (getGEPIndex() != -1)
			alloc = getLLVMValue(func);
		else {
			alloc = Builder->CreateAlloca(matrixType, dataAddrSpace, 0, name);
			if (debug_info) {
				RobDbgInfo.emitLocation(this);
				RobDbgInfo.declareVar(this, alloc, allocblock);
			}
		}

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

Node* Matrix::accept(Visitor& v) {
	return v.visit(*this);
}


DataType Matrix::getDataType() {
	if (matrixType == NULL)
		createDataType();
	return dt;
}

void Matrix::createDataType() {
	if (matrixType != NULL)
		return;

	//Get Type of elements in Vector of Elements, and define as I.
	element_dt = melements->getMatrixType();
	dt = buildTypes->getArrayType(buildTypes->name(element_dt),
		this->getLoc(), 2, true);
	Type* I = buildTypes->llvmType(element_dt);
	
	// The matrix type and size
	rows = melements->getRowCount();
	cols = melements->getColumnCount();
	matrixType = ArrayType::get(I, rows * cols);
}

Type* Matrix::getLLVMType() {
	createDataType();
	return matrixType;
}
