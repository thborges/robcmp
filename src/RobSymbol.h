#ifndef __ROBSYMBOL_H__
#define __ROBSYMBOL_H__

class RobSymbol {
public:
	Value* value;
	Type* pointerType;
	bool isVolatile;
    
	RobSymbol(Value *v, bool isVolatile = false, Type *pointerType = NULL): 
		value(v), isVolatile(isVolatile), pointerType(pointerType) {

    }
};

#endif
