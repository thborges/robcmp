#ifndef __DELAY_H__
#define __DELAY_H__
#include "Node.h"
#include "Int32.h"

class Delay: public Node {
private:
	Node *ms;
	
public:
	Delay (Node *mseg);
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};

#endif
