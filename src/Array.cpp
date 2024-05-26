#include "Array.h"
#include "ArrayElements.h"
#include "Coercion.h"
#include "BackLLVM.h"
#include "Visitor.h"
#include "FunctionImpl.h"
#include "NamedConst.h"
#include "BinaryOp.h"

Array::Array(const string& n, ArrayElements *aes) : Variable(n), elements(aes) {
	NamedConst *nc = new NamedConst("size", getNodeForIntConst(aes->getArraySize()));
	addChild(nc);
}

DataType Array::getDataType() {
	if (arrayType == NULL)
		createDataType();
	return dt;
}

void Array::createDataType() {
	if (arrayType != NULL)
		return;

	//Create a constant with the array size
	size = elements->getArraySize();
	Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
	
	//Get Type of elements in Array of Elements, and define as I.
	element_dt = elements->getArrayType();
	dt = buildTypes->getArrayType(buildTypes->name(element_dt),
		*this->getLoct(), true);
	Type* I = buildTypes->llvmType(element_dt);

	//Declare array type.
	arrayType = ArrayType::get(I, size);
}

Value *Array::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	createDataType();
	
	//Generate array elements
	unsigned int struct_size = elements->getStructSize();
	unsigned int index = 0;
	bool allConst = true;
	vector<Value*> elementValues;
	elementValues.reserve(elements->getArraySize());
	for (int i=0; i<struct_size; i++) {
		Node* elValue = elements->getStructElement(i);
		Value *val = elValue->generate(func, block, allocblock);
		if (!val)
			return NULL;
		val = Coercion::Convert(val, arrayType->getElementType(), block, elValue);
		if (!dyn_cast<Constant>(val))
			allConst = false;

		unsigned elCount = elements->getElementCount(i);
		for (int j=0; j < elCount; j++) {
			elementValues.push_back(val);
		}
	}

	if (!allConst && (allocblock == NULL || allocblock == global_alloc)) {
		// Load will produce an error informing the usage of other variables 
		// to define a new global variable
		return NULL;
	}

	auto sp = RobDbgInfo.currScope();
	auto funit = RobDbgInfo.currFile();

	//Allocate array.
	if (allocblock == global_alloc) { // when alloc is global
		vector<Constant*> constantValues;
		constantValues.reserve(elementValues.size());
		for(auto &a : elementValues)
			constantValues.push_back(dyn_cast<Constant>(a));
		ArrayRef<Constant*> constantRefs(constantValues);
		GlobalVariable *gv = new GlobalVariable(*mainmodule, arrayType, 
			false, GlobalValue::InternalLinkage, 
			ConstantArray::get(arrayType, constantRefs), name);
		gv->setDSOLocal(true);
		gv->setAlignment(Align(2));
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
			alloc = Builder->CreateAlloca(arrayType, dataAddrSpace, 0, name);
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
			Value* gep = Builder->CreateGEP(arrayType, alloc, 
				ArrayRef<Value*>(indexList), "elem");
			store = Builder->CreateStore(elementValues[index], gep, false);
		}
	}

	return alloc;
}

void Array::accept(Visitor& v) {
	v.visit(*this);
}

Type* Array::getLLVMType() {
	createDataType();
	return arrayType;
}

Node *Array::getElementIndex(Node *p1, Node *p2, const string& name, int p1size, int p2size,
	Node *columnNumber) {

	// if constant, validate indexes
	if (p1->isConstExpr() && p1size != -1) {
		Value *p1v = p1->generate(NULL, NULL, NULL);
		Constant *c = dyn_cast<Constant>(p1v);
		int64_t v = c->getUniqueInteger().getZExtValue();
		if (v >= p1size) {
			yyerrorcpp(string_format("Index (%d) for %s is out of bounds.",
				v, name.c_str()), p1);
		}
	}

	if (p2 && p2->isConstExpr() && p2size != -1) {
		Value *p1v = p2->generate(NULL, NULL, NULL);
		Constant *c = dyn_cast<Constant>(p1v);
		int64_t v = c->getUniqueInteger().getZExtValue();
		if (v >= p2size) {
			yyerrorcpp(string_format("Index (%d) for %s is out of bounds.",
				v, name.c_str()), p2);
		}
	}

	if (!p2) // is an array
		return p1;

	// Generate index of element for matrix
	return new BinaryOp(new BinaryOp(p1, '*', columnNumber), '+', p2);
}
