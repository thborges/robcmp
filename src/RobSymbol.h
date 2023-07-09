#ifndef __ROBSYMBOL_H__
#define __ROBSYMBOL_H__

class RobSymbol: public SourceLocation {
public:
	Value* value;
	Type* pointerType;
	DataQualifier qualifier;
	unsigned int matrixLines;
	unsigned int matrixCols;
    
	RobSymbol(Value *v, DataQualifier qualifier = qnone, Type *pointerType = NULL): 
		value(v), qualifier(qualifier), pointerType(pointerType) {
		matrixLines = matrixCols = 0;
    }
};

#endif
