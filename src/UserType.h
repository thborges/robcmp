
#pragma once

#include "Node.h"

class Visitor;

class UserType: public NamedNode {
private:
    vector<string> implements;
    map<string, unsigned> startBits;
    bool declaration = false;
    UserType *parent = NULL;
    unsigned bitWidth = 0;

    bool createDataType();
    void setNestedParent();

public:

	UserType(const string name, vector<Node*> &&stmts, location_t loc):
        NamedNode(name, std::move(stmts), loc) {
        setNestedParent();
    }

    UserType(const string name, vector<Node*> &&stmts, vector<string> &&implements, location_t loc):
        NamedNode(name, std::move(stmts), loc), implements(std::move(implements)) {
        setNestedParent();
    }

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

    virtual const string getTypeName() const;

    virtual void addSymbol(NamedNode *nm) override;

    unsigned getBitWidth() {
        return bitWidth;
    }

    bool implementsInterface(const string& intf) {
        return std::find(implements.begin(), implements.end(), intf) != implements.end();
    }

    DataType getDataType() override {
        if (parent) {
            // forces the definition of the parent first, as it adds the 
            // parent field on subtypes and also create them
            parent->getDataType();
        } else
            createDataType();
        return dt;
    }
};
