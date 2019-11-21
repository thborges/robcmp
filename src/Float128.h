#ifndef __FLOAT128_H__
#define __FLOAT128_H__
#include "Node.h"

class Float128: public Node {
private:
	float number;
public:
	Float128(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
