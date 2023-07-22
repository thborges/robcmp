#ifndef __ROBSYMBOL_H__
#define __ROBSYMBOL_H__

class RobSymbol: public SourceLocation {
public:
	Value* value;
	DataQualifier qualifier;
	unsigned int matrixLines;
	unsigned int matrixCols;
	Structure *structure;
	BasicDataType dt;
	BasicDataType pointee_dt;
	FunctionParams *params;
	bool isDeclaration;
    
	RobSymbol(Value *v, DataQualifier qualifier = qnone): 
		value(v), qualifier(qualifier) {
		matrixLines = matrixCols = 0;
		structure = nullptr;
		dt = tvoid;
		pointee_dt = tvoid;
		params = nullptr;
		isDeclaration = false;
    }
};

#endif
