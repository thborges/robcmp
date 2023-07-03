
#pragma once

class Int1: public Node {
	private:
		char number;
	public:
		Int1(char n): number(n) {}
		char getNumber() const { return number; }
		virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
		virtual void accept(Visitor &v) override;
};
