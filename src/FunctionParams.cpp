
#include "FunctionParams.h"

FunctionParams::FunctionParams() {};

void FunctionParams::append(Variable *e) {
	parameters.push_back(e);
};

void FunctionParams::insert(int at, Variable *fp) {
	parameters.insert(parameters.begin() + at, fp);
}
	
unsigned FunctionParams::getNumCodedParams() {
	unsigned num = 0;
	for(auto p : parameters) {
		// don't count parameters _this, _parent, and other pseudo 
		// parameters like _any_.size, _any_.cols
		if (p->getName() != "_this" && p->getName() != "_parent" &&
			p->getName().find('.') == string::npos)
			num++;
	}
	return num;
};

DataType FunctionParams::getParamType(int position) {
	return parameters[position]->getDataType();
}

const string FunctionParams::getParamName(int position) {
	return parameters[position]->getName();
}
