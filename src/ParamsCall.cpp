
#include "ParamsCall.h"

ParamsCall::ParamsCall() {};

void ParamsCall::append(Node *n) {
	parameters.push_back(n);
};
	
unsigned ParamsCall::getNumParams() const {
	return parameters.size();
};

Node *ParamsCall::getParamElement(int position) const {
	return parameters[position];
}
