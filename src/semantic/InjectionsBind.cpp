
#include "InjectionsBind.h"
#include "Program.h"
#include "UserType.h"
#include "BackLLVM.h"
#include "FunctionCall.h"
#include "Load.h"

Node* InjectionsBind::visit(Node& n) {
    for (auto* child : n.children()) {
        child->accept(*this);
    }
    return NULL;
}

bool InjectionsBind::validate() {
    bool result = true;

    for(auto &[key, ij] : injections) {
        location_t loc = program->getLoc();

        Identifier to(key, loc);
        Identifier bind(ij->bind, loc);

        // injection validation
        auto subTypeName = regex_replace(bind.getFullName(), regex("\\."), "."); //internal types use :
        Identifier bindSubtypes(subTypeName, loc);
        Node *injectType = bindSubtypes.getSymbol(program, false);

        DataType destinationTy = BuildTypes::undefinedType;
        string destinationTyName;
        UserType *bindUserTy = dynamic_cast<UserType*>(injectType);
        if (!bindUserTy) {
            yyerrorcpp(string_format("Bind symbol %s is not of a bindable type.",
                bind.getFullName().c_str()), &ij->loc);
            result = false;
        } else {
            Node *nodeTo = to.getSymbol(program, false);
            if (!nodeTo) {
                yyerrorcpp(string_format("Injection destination %s not found.",
                    to.getFullName().c_str()), &ij->loc);
                result = false;
            } else {
                // Warn: can't call getDataType at this stage
                Variable *var = dynamic_cast<Variable*>(nodeTo);
                assert(var && "Bind symbol should be a var.");
                FunctionCall *fc = dynamic_cast<FunctionCall*>(var->getExpr());
                bool isInterface = false;
                if (fc) {
                    destinationTyName = fc->getIdent().getFullName();
                    destinationTy = buildTypes->getType(destinationTyName);
                    isInterface = destinationTy != BuildTypes::undefinedType &&
                        buildTypes->isInterface(destinationTy);
                }

                if (!isInterface) {
                    yyerrorcpp(string_format("Can not bind %s to %s, as it is not an interface.",
                        bind.getFullName().c_str(), to.getFullName().c_str()), bindUserTy);				
                    result = false;
                } else {
                    if (!bindUserTy->implementsInterface(destinationTyName)) {
                        yyerrorcpp(string_format("Bind symbol %s does not implements %s.",
                            bind.getFullName().c_str(), destinationTyName.c_str()), bindUserTy);				
                        result = false;
                    }
                }
            }
        }
    }

    return result;
}

Node* InjectionsBind::visit(UserType& n) {

    // replace binded interfaces in the AST
    for(auto child : n.children()) {
        Variable *v = dynamic_cast<Variable*>(child);
        if (v && !v->isConstExpr()) {
            string vname = n.getTypeName() + "." + v->getName();
            auto ij = injections.find(vname);
            if (ij != injections.end()) {
                Identifier ident(ij->second->bind, v->getLoc());
                DataType bindDt = ident.getSymbol(program, false)->getDataType();

                // replace the FunctionCall with a Load
                Node *expr = v->getExpr();
                if (FunctionCall *fcall = dynamic_cast<FunctionCall*>(expr)) {
                    Load *ld = new Load(Identifier(ij->second->singletonName, n.getLoc()));
                    ld->setScope(fcall->getScope());
                    ld->setDataType(bindDt);
                    v->setExpr(ld);
                    delete fcall;
                }
            }
        }
    }

    return NULL;
}
