#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector: public Node {
private:
	string name;
	unsigned int size;
	ArrayElements *elements;
public:
	Vector(const char *n, ArrayElements *aes) : name(n), elements(aes) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
