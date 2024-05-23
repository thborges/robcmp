#pragma once

#include "Node.h"
#include "Variable.h"

class FunctionParams {
private:
	std::vector<Variable*> parameters;

public:
	FunctionParams();
	void append(Variable *fp);
	void insert(int at, Variable *fp);
	
	unsigned getNumCodedParams();
	DataType getParamType (int position);
	const string getParamName (int position);

	std::vector<Variable*> const& getParameters() {
		return parameters;
	}
};
