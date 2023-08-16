
#pragma once

#include "HeaderExternals.h"
#include "Node.h"
#include "Scalar.h"

class Visitor;

class UserType: public NamedNode {
private:
    vector<string> implements;
    map<string, unsigned> startBits;
    bool declaration = false;
    UserType *parent = NULL;
    unsigned bitWidth = 0;

    bool createDataType();

public:

	UserType(const string name, vector<Node*> &&stmts): NamedNode(name, std::move(stmts)) { }

    UserType(const string name, vector<Node*> &&stmts, vector<string> &&implements):
        NamedNode(name, std::move(stmts)), implements(std::move(implements)) { }

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

    void accept(Visitor& v) override;

    unsigned getFieldStartBit(Node *field);

    void setDeclaration(bool d) {
        declaration = d;
    }

    UserType* getParent() {
        return parent;
    }

    void setParent(UserType *ut) {
        parent = ut;
    }

    virtual const string getName() const override;

    virtual void addSymbol(NamedNode *nm) override;

    unsigned getBitWidth() {
        return bitWidth;
    }

};
