
#include "FunctionParams.h"

FunctionParams::FunctionParams() {};

void FunctionParams::append(FunctionParam *e) {
	parameters.push_back(e);
};
	
unsigned FunctionParams::getNumCodedParams() {
	unsigned num = 0;
	for(auto p : parameters) {
		if (p->getName()[0] != ':') // don't count parameters :this and :parent
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
