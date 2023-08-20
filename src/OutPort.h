
#pragma once

#include "Node.h"
#include "Int8.h"
#include "Int16.h"
#include "Float.h"

class OutPort: public Node {
private:
	Int8 port;
	Node *expr;
public:
	OutPort (const char *p, Node *e);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
