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
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual bool isConstExpr() override {
		return true;
	}

	virtual DataType getDataType() override {
		return tint16;
	}

};

#endif
