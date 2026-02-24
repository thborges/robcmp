#ifndef __LOOP_H__
#define __LOOP_H__

#include "Node.h"

class InfinityLoop: public Node {
public:
	InfinityLoop(vector<Node*> &&stmts, location_t loc);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};

#endif
