#ifndef __INT64_H__
#define __INT64_H__

class Int64: public Node {
private:
	int number;
	bool IsSigned;
public:
	Int64(int n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
	int getNumber() const { return number; }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor &v) override;
	virtual bool isConstExpr() override {
		return true;
	}
	virtual Type *getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) override {
		return Type::getInt64Ty(global_context);
	}
};

#endif
