#ifndef __FLOAT128_H__
#define __FLOAT128_H__
#include "Node.h"

class Float128: public Node {
private:
	float number;
public:
	Float128(float n): number(n) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	
	virtual bool isConstExpr() override {
		return true;
	}
	
	virtual DataType getDataType() override {
		return tldouble;
	}
};

#endif
