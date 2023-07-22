#ifndef __FLOAT_H__
#define __FLOAT_H__
#include "Node.h"

class Float: public Node {
private:
	float number;
public:
	Float(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override {
		return true;
	}
	virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return tfloat;
	}
};

#endif
