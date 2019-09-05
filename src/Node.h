#ifndef NODE_H
#define NODE_H

class Node {
public:
	virtual bool isFunctionDecl() { return false; }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) = 0;
	virtual ~Node() {}
};
#endif
