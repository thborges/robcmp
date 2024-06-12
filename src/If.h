#pragma once

#include "Node.h"

class If: public Node {
private:
	Node *expr;
	Node *thenst;
	Node *elsest;
public:
	If(Node *e, vector<Node*> &&tst, location_t loc);
	If(Node *e, vector<Node*> &&tst, vector<Node*> &&est, location_t loc);
	virtual Value* generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual Node* accept(Visitor& v) override;
};
