#include "Header.h"

Value *Matrix::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

	/*
	 * Matrix is generated as an array and accessed latter accordingly!
	 */
	
	//Get Type of elements in Vector of Elements, and define as I.
	Type* I = robTollvmDataType[melements->getMatrixType(block, allocblock)];
	
	// The matrix size
	unsigned int lines = melements->getLineCount();
	unsigned int cols = melements->getColumnCount();
	ArrayType* arrayType = ArrayType::get(I, lines * cols);

	// Allocate elements. Supported formats:
	// {{1:3}:3, {1:2,2}:2}
	// {{1,1,1},{1,1,1},{1,1,1},{1,1,2},{1,1,2}}
	bool allConst = true;
	vector<Value*> elementValues;
	elementValues.reserve(lines * cols);
	for(MatrixElement& i: melements->elements) {
		unsigned elCount = i.count;
		
		for (int j=0; j<elCount; j++) {
			for(ArrayElement& k: i.array->elements) {
				Node* elValue = k.value;
				Value *val = elValue->generate(func, block, allocblock);
				if (!val)
					return NULL;
				val = Coercion::Convert(val, I, block, elValue);
				if (!dyn_cast<Constant>(val))
					allConst = false;
				for (int l=0; l<k.count; l++)
					elementValues.push_back(val);
			}
		}
	}

	if (!allConst && (allocblock == NULL || allocblock == global_alloc)) {
		// Load will produce an error informing the usage of other variables 
		// to define a new global variable
		return NULL;
	}

	//Allocate matrix as a vector.
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
	} else {
		var = new AllocaInst(arrayType, 0, name, allocblock);

		Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		StoreInst *store = NULL;
		for(unsigned index = 0; index < elementValues.size(); index++) {
			Value *idx = ConstantInt::get(Type::getInt32Ty(global_context), index);
			Value* indexList[2] = {zero, idx};
			GetElementPtrInst* gep = GetElementPtrInst::Create(arrayType, var, 
				ArrayRef<Value*>(indexList), "", block);
			store = new StoreInst(elementValues[index], gep, false, block);
		}
	}

	//Add array to table of symbols.
	tabelasym[allocblock][name] = new RobSymbol(var);
	tabelasym[allocblock][name]->matrixLines = lines;
	tabelasym[allocblock][name]->matrixCols = cols;

	return var;
}
