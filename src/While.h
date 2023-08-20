
#pragma once

#include "Node.h"

class While: public Node {
private:
	Node *expr;
	Node *stmts;
	
public:
	While(Node *e);
	While(Node *e, vector<Node*> &&stmts);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};
