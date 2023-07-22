#ifndef __INT32_H__
#define __INT32_H__

class Int32: public Node {
private:
	int number;
	bool IsSigned;
public:
	Int32(int n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
	int getNumber() const { return number; }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor &v) override;

	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override {
		return true;
	}
	virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return tint32;
	}
};

#endif
