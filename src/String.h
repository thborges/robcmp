#ifndef __STRING_H__
#define __STRING_H__
#include "Node.h"

class String: public Node {
private:
	string str;
public:
	String(const char *s): str(s) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock); 
};

#endif
