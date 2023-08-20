#pragma once

#include "Node.h"

class If: public Node {
private:
	Node *expr;
	Node *thenst;
	Node *elsest;
public:
	If(Node *e, vector<Node*> &&tst);
	If(Node *e, vector<Node*> &&tst, vector<Node*> &&est);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor& v) override;
};
