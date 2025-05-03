
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
    void createTempDataType();

public:

	UserType(const string name, vector<Node*> &&stmts, location_t loc):
        NamedNode(name, std::move(stmts), loc) {
        setNestedParent();
        createTempDataType();
    }

    UserType(const string name, vector<Node*> &&stmts, vector<string> &&implements, location_t loc):
        NamedNode(name, std::move(stmts), loc), implements(std::move(implements)) {
        setNestedParent();
        createTempDataType();
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

    const vector<string>& implementedIntfs() {
        return implements;
    }

    friend class PropagateTypes;
};
