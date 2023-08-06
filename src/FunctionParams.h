#pragma once

#include "Node.h"
#include "Variable.h"

class FunctionParam: public Variable {
public:
	FunctionParam(const char *name, DataType dt): Variable(name) {
		this->dt = dt;
	}
		
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
		return NULL;
	}

	void setAlloca(Value *alloc) {
		this->alloc = alloc;
	}

	friend class FunctionImpl;
};

class FunctionParams {
private:
	std::vector<FunctionParam*> parameters;

public:
	FunctionParams();
	void append(FunctionParam *fp);
	
	unsigned getNumParams();
	DataType getParamType (int position);
	const string getParamName (int position);

	std::vector<FunctionParam*> const& getParameters() {
		return parameters;
	}
};
