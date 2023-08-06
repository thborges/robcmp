#ifndef __INPORT_H__
#define __INPORT_H__
#include "Node.h"
#include "Int8.h"

class InPort: public Node {
private:
	string port;
public:
	InPort(const char *p): port(p) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif
