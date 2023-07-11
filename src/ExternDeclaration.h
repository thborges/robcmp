#ifndef __EXTERNDECLARATION_H__
#define __EXTERNDECLARATION_H__
#include "Node.h"

class ExternDeclaration: public Node {
private:
	LanguageDataType tipo;
	string name;
	FunctionParams *parameters;
public:
	ExternDeclaration(LanguageDataType tipo, string name, FunctionParams *fp) {
		this->tipo = tipo;
		this->name = name;
		this->parameters = fp;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
};

#endif
