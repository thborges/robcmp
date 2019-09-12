#ifndef __INT32_H__
#define __INT32_H__

class Int32: public Node {
private:
	int number;
public:
	Int32(int n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
	/*{
		return ConstantInt::get(Type::getInt32Ty(global_context), number);
	}*/
};

#endif
