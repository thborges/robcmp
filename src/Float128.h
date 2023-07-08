#ifndef __FLOAT128_H__
#define __FLOAT128_H__
#include "Node.h"

class Float128: public Node {
private:
	float number;
public:
	Float128(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	
	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override {
		return true;
	}
	
	virtual Type *getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return Type::getFP128Ty(global_context);
	}
};

#endif
