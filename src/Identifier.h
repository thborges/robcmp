
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

    string const getLastName() const;
};
