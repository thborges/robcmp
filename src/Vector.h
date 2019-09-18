#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector: public Node {
private:
	string name;
	unsigned int size;
	Node *expr;
public:
	Vector(const char *n, Node *e) : name(n), expr(e) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
