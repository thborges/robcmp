
#pragma once

#include "Node.h"

class Interface: public NamedNode {
private:
	void createDataType();

public:
	Interface(const string& name, location_t loc) : NamedNode(name, loc) {
		createDataType();
	}

    Interface(const string& name, vector<Node*> stmts, location_t loc):
		NamedNode(name, std::move(stmts), loc) {
		createDataType();
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	bool validateImplementation(UserType *ut);

	
};
