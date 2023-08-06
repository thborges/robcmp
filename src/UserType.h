
#pragma once

#include "HeaderExternals.h"
#include "Node.h"
#include "Scalar.h"

class Visitor;

class UserType: public NamedNode {
private:
    vector<string> implements;
    void createDataType();

public:

	UserType(const string name, vector<Node*> &&stmts): NamedNode(name, std::move(stmts)) { }

    UserType(const string name, vector<Node*> &&stmts, vector<string> &&implements):
        NamedNode(name, std::move(stmts)), implements(std::move(implements)) { }

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

    void accept(Visitor& v) override;

};