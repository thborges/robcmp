#include "Header.h"

FunctionParams::FunctionParams() {};

void FunctionParams::append(FunctionParam& e) {
	parameters.push_back(e);
};
	
unsigned FunctionParams::getNumParams() const {
	return parameters.size();
};

LanguageDataType FunctionParams::getParamType(int position) const {
	return parameters[position].type;
}

const char *FunctionParams::getParamElement(int position) const {
	return parameters[position].name;
}
