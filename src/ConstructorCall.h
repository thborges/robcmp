
#pragma once

#include "Node.h"
#include "FunctionImpl.h"
#include "MemCopy.h"

class ConstructorCall: public Constructor {
protected:
	string name;
public:
	ConstructorCall(const string tyName, location_t loc): Constructor(loc), name(tyName) { }
    
	virtual Value* generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	DataType getDataType() override {
		if (dt == BuildTypes::undefinedType)
			dt = buildTypes->getType(name);
		return dt;
	}

	virtual map<string, NamedNode*> const& getSymbols() override {
		getDataType();
		if (dt != BuildTypes::undefinedType) {
			auto symbol = findSymbol(name);
			if (symbol)
				return symbol->getSymbols();
		}
		return symbols;
	}
};
