#ifndef __INT8_H__
#define __INT8_H__

class Int8: public Node {
	private:
		char number;
	public:
		Int8(char n): number(n) {}
		char getNumber() const { return number; }
		virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
		virtual void accept(Visitor &v) override;
};

#endif
