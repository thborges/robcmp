
#pragma once

class Array: public Node {
private:
	string name;
	unsigned int size;
	ArrayElements *elements;
public:
	Array(const char *n, ArrayElements *aes) : name(n), elements(aes) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};
