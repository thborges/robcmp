#pragma once

#include "Node.h"
#include "Field.h"

class Load: public Node {
private:
	Identifier ident;
public:
	Load(const char* i): ident(i) {	}
	Load(Identifier i): ident(i) { }
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;

	virtual bool isConstExpr() override;

};
