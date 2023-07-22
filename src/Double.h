#ifndef __DOUBLE_H__
#define __DOUBLE_H__
#include "Node.h"

class Double: public Node {
private:
	float number;
public:
	Double(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override {
		return true;
	}
	virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return tdouble;
	}
};

#endif
