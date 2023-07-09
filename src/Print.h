#ifndef __PRINT_H__
#define __PRINT_H__
#include "Node.h"

class Print: public Node {
private:
	Node *expr;
public:
	Print(Node *e) : expr(e) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
