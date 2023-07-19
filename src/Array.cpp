#include "Header.h"

Value *Array::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	//Create an Array of Type Int8, and Size = size.
	size = elements->getArraySize();
	Value *array_size = ConstantInt::get(Type::getInt8Ty(global_context), size);
	
	//Get Type of elements in Array of Elements, and define as I.
	LanguageDataType pointee_dt = elements->getArrayType(block, allocblock);
	Type* I = robTollvmDataType[pointee_dt];

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
	Value* var;
	if (allocblock == global_alloc) { // when alloc is global
		vector<Constant*> constantValues;
		constantValues.reserve(elementValues.size());
		for(auto &a : elementValues)
			constantValues.push_back(dyn_cast<Constant>(a));
		ArrayRef<Constant*> constantRefs(constantValues);
		GlobalVariable *gv = new GlobalVariable(*mainmodule, arrayType, 
			false, GlobalValue::ExternalLinkage, ConstantArray::get(arrayType, constantRefs), name);
		var = gv;

		if (debug_info) {
			 //FIXME: Replace 16 with pointer size for platform!
			auto di_ptr = DBuilder->createPointerType(RobDbgInfo.types[pointee_dt], 16);
			auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
				funit, lineno, di_ptr, false);
			gv->addDebugInfo(d);
		}

	} else {
		Builder->SetInsertPoint(allocblock);
		var = Builder->CreateAlloca(arrayType, 0, name);

		RobDbgInfo.emitLocation(this);
		Builder->SetInsertPoint(block);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		StoreInst *store = NULL;
		for(unsigned index = 0; index < elementValues.size(); index++) {
			Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), index);
			Value* indexList[2] = {zero, idx};
			Value* gep = Builder->CreateGEP(arrayType, var, 
				ArrayRef<Value*>(indexList), "elem");
			store = Builder->CreateStore(elementValues[index], gep, false);
		}
	}

	//Add array to table of symbols.
	RobSymbol *rs = new RobSymbol(var);
	rs->dt = tarray;
	rs->pointee_dt = pointee_dt;
	tabelasym[allocblock][name] = rs;
	return var;
}
