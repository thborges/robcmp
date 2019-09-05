#ifndef __FLOAT_H__
#define __FLOAT_H__
#include "Node.h"

class Float: public Node {
private:
	float number;
public:
	Float(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantFP::get(Type::getFloatTy(global_context), number);
	}
};

#endif
