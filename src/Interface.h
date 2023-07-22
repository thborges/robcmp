
#pragma once

#include "Node.h"

class Interface: public NamedNode {
public:
    Interface(const string name): NamedNode(name) {}

	Interface(const string name, vector<Node *> &&funcs): NamedNode(name, std::move(funcs)) {}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	bool validateImplementation(UserType *ut);
};
