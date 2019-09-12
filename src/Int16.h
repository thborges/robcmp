#ifndef __INT16_H__
#define __INT16_H__
#include "Node.h"

class Int16: public Node {
private:
	short number;
public:
	Int16(short n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
