#ifndef __LOOP_H__
#define __LOOP_H__

#include "Node.h"

class Loop: public Node {
public:
	Loop(vector<Node*> &&stmts);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};

#endif
