
#include "VirtualDispatchPasses.h"
#include "FunctionCall.h"
#include "Program.h"
#include "UserType.h"
#include "BackLLVM.h"
#include "ConstructorCall.h"

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
   
    // We are looking for intf.method(...) calls, anywhere.
    // if there's one and the stem is not injected, it's a call that needs virtual dispatch
    
    // get the symbol containing the function being called
    LoadBase *stem = n.getStem();
    if (stem) {
        Load *ld = dynamic_cast<Load*>(stem);
        if (!ld)
            return NULL;
        // can't call ld.getIdentSymbol at this point
        Identifier ident(ld->getName(), ld->getLoc());
        Node *stemSymbol = ident.getSymbol(n.getScope(), false);
        
        // Currently, bind points are only vars at global and user type field
        Node *scope = stemSymbol->getScope();
        bool isBindable = scope == program || dynamic_cast<UserType*>(scope);

        if (isBindable) {
            // get the complete hierarquical name, if it's a inner type implementation
            auto stem_full_name = stemSymbol->getName();
            if (UserType *owner = dynamic_cast<UserType*>(stemSymbol->getScope())) {
                stem_full_name = regex_replace(owner->getTypeName(), regex(":"), ".");
                stem_full_name.append(".");
                stem_full_name.append(stemSymbol->getName());
            }
            
            // identify if an injection for the symbol exists
            auto ij = injections.find(stem_full_name);
            Node *ijsymbol = NULL;
            if (ij != injections.end())
                ijsymbol = Identifier(ij->first, program->getLoc()).getSymbol(program);
            
            if (ijsymbol == stemSymbol) {
                // change the call to the injected symbol if singleton
                if (ij->second->scope == bs_singleton) {
                    string new_call = ij->second->bind + ":" + n.getIdent().getFullName();
                    identifiedCalls.push_back(CompileTimeInject{&n, new_call});
                }
            }
        }

        // if no injection exists with that name, or the names refer to distinct symbols,
        // then there's a call to a method of an unbound interface 
        // PropagateTypes didn't run at this point, so don't call getDataType here
        if (stemSymbol->dt != BuildTypes::undefinedType && 
            buildTypes->isInterface(stemSymbol->dt)) {
            program->getDispatcher()->addIntfInvocation(stemSymbol->dt);
        }
    }
    return NULL;
}

void IdentifyVirtualDispatch::applyIdentifiedChanges() {
    for(auto &ic : identifiedCalls) {
    }
}