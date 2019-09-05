#ifndef __INPORT_H__
#define __INPORT_H__
#include "Node.h"
#include "Int8.h"

class InPort: public Node {
private:
	string port;
public:
	InPort(const char *p): port(p) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;
		
		Int8 prt(atoi(port.c_str()));
		args.push_back(prt.generate(func, block, allocblock));
		
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(analogRead, argsRef, "", block);
	}
};

#endif
