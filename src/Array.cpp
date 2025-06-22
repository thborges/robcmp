#include "Array.h"
#include "ArrayElements.h"
#include "BackLLVM.h"
#include "FunctionImpl.h"
#include "NamedConst.h"
#include "BinaryOp.h"
#include "semantic/PropagateTypes.h"
#include "semantic/Visitor.h"

Array::Array(const string& n, ArrayElements *aes, location_t loc) : Variable(n, loc), arrayElements(aes) {
	NamedConst *nc = new NamedConst("size", getNodeForUIntConst(aes->getArraySize(), loc));
	addChild(nc);
	addSymbol(nc);
}

Array::Array(const string& n, location_t loc) : Variable(n, loc) {
	arrayElements = new ArrayElements(getLoc());
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
	size = arrayElements->getArraySize();
	
	//Get Type of elements in Array of Elements, and define as I.
	element_dt = arrayElements->getArrayType();
	dt = buildTypes->getArrayType(buildTypes->name(element_dt),
		this->getLoc(), 1, true);
	
	Type* I = buildTypes->llvmType(element_dt);
	if (buildTypes->isComplex(element_dt)) {
		// in rob, all arrays of user types (complex types)
		// are array of references
		I = I->getPointerTo(codeAddrSpace);
	}

	//Declare array type.
	arrayType = ArrayType::get(I, size);
}

Value *Array::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	
	createDataType();
	
	//Generate array elements
	unsigned int index = 0;
	bool allConst = true;
	vector<Value*> elementValues;
	map<int, Constructor*> ctorsValues;
	
	int currentElement = 0;
	elementValues.reserve(arrayElements->getArraySize());
	unsigned int struct_size = arrayElements->getStructSize();
	for (int i=0; i<struct_size; i++) {
		Node* elValue = arrayElements->getStructElement(i);
		Value *val;
		Constructor *ctor;
		if ((ctor = dynamic_cast<Constructor*>(elValue))) {
			// constructors are called latter, for each array element
			val = nullptr;
			allConst = false;
		} else {
			ctor = nullptr;
			val = elValue->generate(func, block, allocblock);
			if (!val) {
				yyerrorcpp(string_format("Can not generate the value for element at pos %d", i).c_str(), elValue, true);
				return NULL;
			}
			if (!dyn_cast<Constant>(val))
				allConst = false;
		}

		unsigned elCount = arrayElements->getElementCount(i);
		for (int j=0; j < elCount; j++) {
			elementValues.push_back(val);
			if (!val) // is ctor
			 	ctorsValues[currentElement] = ctor;
			currentElement++;
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

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);

		// create an array and initialize the Copy/Constructors instances
		// e.g. a = {element(), element():2, copy(x1), copy(y)}
		if (ctorsValues.size() > 0) {
			Type* ctorTy = buildTypes->llvmType(element_dt);
			ArrayType *ctorArrayType = ArrayType::get(ctorTy, ctorsValues.size());
			Builder->SetInsertPoint(allocblock);
			Value *ctorArray = Builder->CreateAlloca(ctorArrayType, dataAddrSpace, 0, "inlineArrayElems");
			
			Builder->SetInsertPoint(block);
			int idxCtor = 0;
			for(auto &[key, ctor] : ctorsValues) {
				Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), idxCtor);
				Value* indexList[2] = {zero, idx};
				RobDbgInfo.emitLocation(ctor);
				Value* gep = Builder->CreateGEP(ctorArrayType, ctorArray, indexList, "ctorElem");
				ctor->setLeftGEP(gep);
				ctor->generate(func, block, allocblock);
				elementValues[key] = gep;
				idxCtor++;
			}
		}

		RobDbgInfo.emitLocation(this);
		Builder->SetInsertPoint(block);

		// set array elements
		for(unsigned index = 0; index < elementValues.size(); index++) {
			Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), index);
			Value* indexList[2] = {zero, idx};
			Value* gep = Builder->CreateGEP(arrayType, alloc, indexList, "elem");
			Builder->CreateStore(elementValues[index], gep, false);
		}
	}

	return alloc;
}

Node* Array::accept(Visitor& v) {
	return v.visit(*this);
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
	Node *i16p1;
	if (buildTypes->isSignedDataType(p1->getDataType()))
		i16p1 = new SExtInt(p1, tint16);
	else
	 	i16p1 = new ZExtInt(p1, tint16u);
	BinaryOp *op = new BinaryOp(new BinaryOp(i16p1, '*', columnNumber), '+', p2);
	PropagateTypes pt;
	pt.visit(*op);
	return op;
}
