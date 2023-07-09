#ifndef __LOOP_H__
#define __LOOP_H__

#include "Node.h"

class Loop: public Node {
private:
	Node *stmts;
public:
	Loop(Node *stms);
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor& v) override;
};

#endif
