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
	switch (var){
		case 1:
			return Type::getInt1Ty(global_context); //Integer - 1 bit
			break;
		case 2:
			return Type::getInt8Ty(global_context); //Integer - 8 bits
			break;
		case 3:
			return Type::getInt16Ty(global_context); //Integer - 16 bits
			break;
		case 4:
			return Type::getInt32Ty(global_context); //Integer - 32 bits
			break;
		case 5:
			return Type::getInt64Ty(global_context); //Integer - 64 bits
			break;
		case 6:
			return Type::getInt128Ty(global_context); //Integer - 128 bits
			break;
		case 7:
			return Type::getHalfTy(global_context); //Short Float - 16 bits
			break;
		case 8:
			return Type::getFloatTy(global_context); //Float - 32 bits
			break;
		case 9:
			return Type::getDoubleTy(global_context); //Integer - 64 bits
			break;
		case 10:
			return Type::getFP128Ty(global_context); //Long Double - 128 bits
			break;
	}
}

const char *FunctionParams::getParamElement(int position) const {
	return parameters[position].name;
}
