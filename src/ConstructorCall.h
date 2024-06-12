
#pragma once

#include "Node.h"
#include "Variable.h"
#include "FunctionImpl.h"

class ConstructorCall: public Node {
protected:
	Variable *leftValue = NULL;
	string name;
public:
	ConstructorCall(const string tyName, location_t loc): Node(loc), name(tyName) { }
	
	virtual void setLeftValue(Variable *symbol) override {
		leftValue = symbol;
	}
    
	virtual Value* generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	DataType getDataType() override {
		if (dt == BuildTypes::undefinedType)
			dt = buildTypes->getType(name);
		return dt;
	}
};
