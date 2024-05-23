
#include "ParamsCall.h"

ParamsCall::ParamsCall() {};

void ParamsCall::append(Node *n) {
	parameters.push_back(n);
};

void ParamsCall::insert(int at, Node *pc) {
	parameters.insert(parameters.begin() + at, pc);
}
	
unsigned ParamsCall::getNumParams() const {
	return parameters.size();
};

Node *ParamsCall::getParamElement(int position) const {
	return parameters[position];
}
