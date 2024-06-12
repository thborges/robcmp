
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

	UserType(const string name, vector<Node*> &&stmts, location_t loc):
        NamedNode(name, std::move(stmts), loc) { }

    UserType(const string name, vector<Node*> &&stmts, vector<string> &&implements, location_t loc):
        NamedNode(name, std::move(stmts), loc), implements(std::move(implements)) { }

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

    Node* accept(Visitor& v) override;

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

    bool implementsInterface(const string& intf) {
        return std::find(implements.begin(), implements.end(), intf) != implements.end();
    }

    DataType getDataType() override {
        createDataType();
        return dt;
    }
};
