#ifndef __DOUBLE_H__
#define __DOUBLE_H__
#include "Node.h"

class Double: public Node {
private:
	float number;
public:
	Double(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual bool isConstExpr() override {
		return true;
	}
	virtual Type *getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return Type::getDoubleTy(global_context);
	}
};

#endif
