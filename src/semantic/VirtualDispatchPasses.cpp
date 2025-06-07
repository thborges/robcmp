
#include "VirtualDispatchPasses.h"
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

        // get the complete hierarquical name
        if (UserType *owner = dynamic_cast<UserType*>(stemSymbol->getScope())) {
            auto full_name = regex_replace(owner->getTypeName(), regex(":"), ".");
            full_name.append(".");
            full_name.append(stem.getFullName());
            stem.changeIdentifier(full_name);
        }
        
        // identify if exists an injection for the symbol
        auto ij = injections.find(stem.getFullName());
        Node *ijsymbol = NULL;
        if (ij != injections.end())
            ijsymbol = Identifier(ij->first, program->getLoc()).getSymbol(program);
          
        if (ijsymbol == stemSymbol) {
            // change the call to the injected symbol if singleton
            if (ij->second->scope == bs_singleton) {
                string new_call = ident.getFullName();
                string to_replace = ident.getStem().getFullName();
                new_call.replace(new_call.find(to_replace), to_replace.length(), ij->second->singletonName);
                identifiedCalls.push_back(CompileTimeInject{&n, new_call});
            }
        } else {
            // if no injection exists with that name, or the names refer to distinct symbols,
            // then there's a call to a method of an unbound interface 
            // PropagateTypes didn't run at this point, so don't call getDataType here
            if (stemSymbol->dt != BuildTypes::undefinedType && 
                buildTypes->isInterface(stemSymbol->dt)) {
                program->getDispatcher()->addIntfInvocation(stemSymbol->dt);
            }
        }
    }
    return NULL;
}

void IdentifyVirtualDispatch::applyIdentifiedChanges() {
    for(auto &ic : identifiedCalls) {
        //errs() << "Call to " << ic.fc->getIdent().getFullName() <<
        //    " converted to " << ic.new_call << "\n";
        ic.fc->changeIdentifier(ic.new_call);
    }
}