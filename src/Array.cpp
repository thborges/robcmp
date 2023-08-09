#include "Array.h"
#include "ArrayElements.h"
#include "Coercion.h"
#include "BackLLVM.h"
#include "Visitor.h"
#include "Int16.h"

Array::Array(const char *n, ArrayElements *aes) : LinearDataStructure(n), elements(aes) {
	NamedConst *nc = new NamedConst("size", getNodeForIntConst(aes->getArraySize()));
	addChild(nc);
}

Value *Array::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	//Create an Array of Type Int8, and Size = size.
	size = elements->getArraySize();
	Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
	
	//Get Type of elements in Array of Elements, and define as I.
	element_dt = elements->getArrayType(func);
	Type* I = buildTypes->llvmType(element_dt);

	//Declare array type.
	ArrayType* arrayType = ArrayType::get(I, size);
	
	//Generate array elements
	unsigned int struct_size = elements->getStructSize();
	unsigned int index = 0;
	bool allConst = true;
	vector<Value*> elementValues;
	elementValues.reserve(elements->getArraySize());
	for (int i=0; i<struct_size; i++) {
		unsigned elCount = elements->getElementCount(i);
		for (int j=0; j<elCount; j++) {
			Node* elValue = elements->getStructElement(i);
			Value *val = elValue->generate(func, block, allocblock);
			if (!val)
				return NULL;
			val = Coercion::Convert(val, I, block, elValue);
			if (!dyn_cast<Constant>(val))
				allConst = false;
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
			auto di_ptr = DBuilder->createPointerType(buildTypes->diType(getElementDt()), 
				buildTypes->bitWidth(currentTarget.pointerType));
			auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
				funit, this->getLineNo(), di_ptr, false);
			gv->addDebugInfo(d);
		}

	} else {
		Builder->SetInsertPoint(allocblock);
		alloc = Builder->CreateAlloca(arrayType, dataAddrSpace, 0, name);

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
