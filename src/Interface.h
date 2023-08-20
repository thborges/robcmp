
#pragma once

#include "Node.h"

class Interface: public NamedNode {
private:
	void createDataType();

public:
	Interface(const string& name) : NamedNode(name) {
		createDataType();
	}

    Interface(const string& name, vector<Node*> stmts): NamedNode(name, std::move(stmts)) {
		createDataType();
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	bool validateImplementation(UserType *ut);

	
};
