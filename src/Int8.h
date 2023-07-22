#ifndef __INT8_H__
#define __INT8_H__

class Int8: public Node {
	private:
		char number;
		bool IsSigned;
	public:
		Int8(char n, bool IsSigned = false): number(n), IsSigned(IsSigned) {}
		char getNumber() const { return number; }
		virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
		virtual void accept(Visitor &v) override;
		virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) override {
			return true;
		}
		virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) override {
			return tint8;
		}
};

#endif
