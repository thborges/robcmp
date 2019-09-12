#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector: public Node {
private:
	string name;
	Node *expr;
public:
	Vector(const char *n) : name(n) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
