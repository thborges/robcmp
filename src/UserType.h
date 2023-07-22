
#pragma once

#include "Node.h"

class UserType: public NamedNode {
private:
    vector<string> implements;

public:

	UserType(const string name, Stmts &&stmts): NamedNode(name, std::move(stmts.node_children)) {}

    UserType(const string name, Stmts &&stmts, vector<string> &&implements):
        NamedNode(name, std::move(stmts.node_children)),
        implements(std::move(implements)) {}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
};
