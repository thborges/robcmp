
#include "Header.h"

Value *Interface::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
    for(const auto n : symbols) {
        printf("Symbol %s exists here!\n", n.first.c_str());
    }
    return NULL;
}

bool Interface::validateImplementation(UserType *ut) {
    bool result = true;
    for(const auto & [key, func_decl] : symbols) {
        auto symb = ut->findSymbol(key, false);
        FunctionImpl *fimpl = dynamic_cast<FunctionImpl*>(symb);
        if (!symb) {
            yyerrorcpp(string_format("Type %s doesn't implement %s.", ut->getName().c_str(),
                key.c_str()), ut);
            yyerrorcpp(string_format("%s is defined here.", key.c_str()), func_decl);
            result = false;
        } else if (!fimpl) {
            yyerrorcpp(key + " must be a function.", symb);
            result = false;
        } else {
            fimpl->validateImplementation(dynamic_cast<FunctionDecl*>(func_decl));
        }
    }
    return result;
}
