#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector: public Node {
private:
	string name;
	unsigned int size;
	Node *expr;
public:
	Vector(const char *n, unsigned int s, Node *e) : name(n), size(s), expr(e) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
