#ifndef __OUTPORT_H__
#define __OUTPORT_H__
#include "Node.h"
#include "Int16.h"
#include "Float.h"

class OutPort: public Node {
private:
	Int8 port;
	Node *expr;
public:
	OutPort (const char *p, Node *e);
	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
