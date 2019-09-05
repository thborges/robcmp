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
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;
		
		Int8 prt(atoi(port.c_str()));
		args.push_back(prt.generate(func, block, allocblock));

		Value *value = expr->generate(func, block, allocblock);
		Value *nvalue = value;
		if (value->getType()->isFloatTy())
			nvalue = new FPToSIInst(value, Type::getInt16Ty(global_context), "trunci", block);

		args.push_back(nvalue);
		//Value *int8v = new TruncInst(value, Type::getInt8Ty(global_context), "", block);
		//args.push_back(int8v);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(analogWrite, argsRef, "", block);
	}
};

#endif
