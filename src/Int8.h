#ifndef __INT8_H__
#define __INT8_H__

class Int8: public Node {
	private:
		char number;
	public:
		Int8(char n): number(n) {}
		virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
			return ConstantInt::get(Type::getInt8Ty(global_context), number);
		}
};

#endif
