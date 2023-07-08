#ifndef __INT16_H__
#define __INT16_H__
#include "Node.h"

class Int16: public Node {
private:
	short number;
	bool IsSigned;
public:
	Int16(short n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
	short getNumber() const { return number; }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor &v) override;
	virtual bool isConstExpr() override {
		return true;
	}
	virtual Type *getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return Type::getInt16Ty(global_context);
	}
};

#endif
