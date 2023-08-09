
#pragma once

#include "Node.h"
#include "Identifier.h"

class Variable: public NamedNode {
protected:
    Value *alloc;
    Identifier ident;

public:
    Variable(const string &name): NamedNode(name), ident(name) {}

    virtual Value* getLLVMValue(Node *stem) override {
        return alloc;
    }
};
