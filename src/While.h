#ifndef __WHILE_H__
#define __WHILE_H__

#include "Node.h"

class While: public Node {
private:
	Node *expr;
	Node *stmts;
public:
	While(Node *e, Node *stms);
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor& v) override;
};

#endif
