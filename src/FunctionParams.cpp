
#include "FunctionParams.h"

FunctionParams::FunctionParams() {};

void FunctionParams::append(FunctionParam *e) {
	parameters.push_back(e);
};
	
unsigned FunctionParams::getNumParams() {
	return parameters.size();
};

DataType FunctionParams::getParamType(int position) {
	return parameters[position]->getDataType();
}

const string FunctionParams::getParamName(int position) {
	return parameters[position]->getName();
}
