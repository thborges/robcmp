#ifndef __DELAY_H__
#define __DELAY_H__
#include "Node.h"
#include "Int32.h"

class Delay: public Node {
private:
	Node *ms;
public:
	Delay (Node *mseg) : ms(mseg) {}
	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif
