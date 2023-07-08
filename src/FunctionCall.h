#ifndef __FUNCTIONCALL_H__
#define __FUNCTIONCALL_H__
#include "Node.h"

class FunctionCall: public Node {
private:
	string name;
	ParamsCall *parameters;
public:
	FunctionCall(string name, ParamsCall *pc) {
		this->name = name;
		this->parameters = pc;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	Type* getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) override;
};

#endif
