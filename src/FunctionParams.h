#ifndef __FUNCTION_PARAMS_H__
#define __FUNCTION_PARAMS_H__

#include "Node.h"

class FunctionParams {
private:
public:
	std::vector<FunctionParam> parameters;
	FunctionParams();
	void append(FunctionParam& fp);
	
	unsigned getNumParams() const;
	BasicDataType getParamType (int position) const;
	const char *getParamElement (int position) const;
};

#endif

