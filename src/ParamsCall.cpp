#include "Header.h"

ParamsCall::ParamsCall() {};

void ParamsCall::append(Node *n) {
	parameters.push_back(n);
};
	
unsigned ParamsCall::getNumParams() const {
	unsigned r = 0;
	for(auto& i : parameters)
		r += 1;
	return r;
};

Type *ParamsCall::getParamType(int position) const {
	// TODO:	
	//Generate Problem
}
