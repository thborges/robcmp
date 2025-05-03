
#include "IdentifyVirtualDispatch.h"
#include "FunctionCall.h"
#include "Program.h"
#include "UserType.h"
#include "BackLLVM.h"

void IdentifyVirtualDispatch::propagateChildren(Node& n) {
    for (auto* child : n.children()) {
        child->accept(*this);
    }
}

Node* IdentifyVirtualDispatch::visit(Node& n) {
    propagateChildren(n);
    return NULL;
}

Node* IdentifyVirtualDispatch::visit(FunctionCall& n) {
    auto& ident = n.getIdent();
    
    if (ident.isComplex()) {
        // get the symbol containing the function being called
        Identifier stem = ident.getStem();
        Node *stemSymbol = stem.getSymbol(n.getScope());
        
        // identify if exists an injection for the symbol
        auto ij = injections.find(stem.getFullName());
        Node *ijsymbol = NULL;
        if (ij != injections.end())
            ijsymbol = Identifier(ij->first, program->getLoc()).getSymbol(program);
        
        // if no injection exists with that name, or the names refer to distinct symbols,
        // then there's a call to a method of an unbound interface 
        if (ij == injections.end() || ijsymbol != stemSymbol) {
            DataType dt = stemSymbol->getDataType();
            if (buildTypes->isInterface(dt)) {
                //errs() << "Identified a call to " << ident.getFullName() << "\n";
                program->getDispatcher()->addIntfInvocation(dt);
            }
        }
    }
    return NULL;
}
