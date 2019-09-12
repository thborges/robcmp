#ifndef __OUTPORT_H__
#define __OUTPORT_H__
#include "Node.h"
#include "Int16.h"
#include "Float.h"

class OutPort: public Node {
private:
	string port;
	Node *expr;
public:
	OutPort (const char *p, Node *e) : port(p), expr(e) {}
	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
