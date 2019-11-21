#ifndef __HALF_H__
#define __HALF_H__
#include "Node.h"

class Half: public Node {
private:
	float number;
public:
	Half(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
