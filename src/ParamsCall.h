#ifndef __PARAMS_CALL_H__
#define __PARAMS_CALL_H__

#include "Node.h"

class ParamsCall {
private:
	std::vector<Node *> parameters;
public:
	ParamsCall();
	void append(Node *pc);
	
	unsigned getNumParams() const;
	Type *getParamType (int position) const;
	Node *getParamElement (int position) const;
};

#endif

