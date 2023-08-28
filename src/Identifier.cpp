
#include "Identifier.h"

Node* Identifier::getSymbol(Node *scope, bool validate) {

    Node *result = scope;
    stringstream ss(ident);
    string ci;

    // first symbol
    getline(ss, ci, '.');
    result = result->findSymbol(ci);
    if (result) {
        while (!ss.eof() && result != NULL) {
            getline(ss, ci, '.');
            result = result->findMember(ci);
        }
    }
    
    if (!result && validate) {
        yyerrorcpp("Symbol " + ci + " not found.", this);
    }
    return result;
}

Identifier Identifier::getStem() {
    assert(complex && "identifier is not complex.");
    size_t last = ident.find_last_of('.');
    return ident.substr(0, last);
}

 string const Identifier::getLastName() const {
    if (!complex)
        return ident;
    else
        return ident.substr(ident.find_last_of(".")+1);
}
