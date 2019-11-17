#include "Header.h"

FunctionParams::FunctionParams() {};

void FunctionParams::append(FunctionParam& e) {
	parameters.push_back(e);
};
	
unsigned FunctionParams::getNumParams() const {
	unsigned r = 0;
	for(auto& i : parameters)
		r += 1;
	return r;
};

Type *FunctionParams::getParamType(int position) const {
	int var = parameters[position].type;
	if (var == 1)
		return Type::getInt16Ty(global_context);
	else if (var == 2)
		return Type::getFloatTy(global_context);
	else
		return Type::getFloatTy(global_context);
}

const char *FunctionParams::getParamElement(int position) const {
	return parameters[position].name;
}
