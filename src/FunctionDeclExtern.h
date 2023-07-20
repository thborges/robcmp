#ifndef __FUNCTIONDECLEXTERN_H__
#define __FUNCTIONDECLEXTERN_H__

#include "Node.h"

class FunctionDeclExtern: public Node {
private:
	LanguageDataType tipo;
	string name;
	FunctionParams *parameters;
public:
	FunctionDeclExtern(LanguageDataType tipo, string name, FunctionParams *fp){
		this->tipo = tipo;
		this->name = name;
		this->parameters = fp;
	}
	
	bool isFunctionDecl() {
		return true;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif

