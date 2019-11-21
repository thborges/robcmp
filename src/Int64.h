#ifndef __INT64_H__
#define __INT64_H__

class Int64: public Node {
private:
	int number;
public:
	Int64(int n): number(n) {}
	int getNumber() const { return number; }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor &v) override;
};

#endif
