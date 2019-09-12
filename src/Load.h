#ifndef __LOAD_H__
#define __LOAD_H__
#include "Node.h"

class Load: public Node {
private:
	string ident;
public:
	Load(const char *i): ident(i) {}

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};
#endif
