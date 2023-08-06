
#pragma once

#include "Node.h"

class Identifier: public SourceLocation {
private:
    string ident;
    bool complex;

public:
    Identifier(const string& ident): ident(ident) {
        complex = ident.find('.') != string::npos;
    }

    Node* getSymbol(Node *scope, bool validate = true);

    string const getFullName() const {
        return ident;
    }

    bool isComplex() {
        return complex;
    }

    Identifier getStem();
};

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
