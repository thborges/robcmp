
#pragma once

#include "Node.h"

class While: public Node {
private:
	Node *expr;
	Node *stmts;
	
public:
	While(Node *e, location_t loc);
	While(Node *e, vector<Node*> &&stmts, location_t loc);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};
