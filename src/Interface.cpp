
#include "Interface.h"
#include "UserType.h"
#include "FunctionImpl.h"
#include "FunctionDecl.h"

void Interface::createDataType() {
    // TRY: prevent opaque type
    // the interface type is replaced at link stage
    /*Scalar *no_opaque = new Scalar("no_opaque", new Int1(0));
    no_opaque->setGEPIndex(0);
    addChild(no_opaque);
    addSymbol(no_opaque);
    
    std::vector<Type*> elements;
    elements.push_back(Type::getInt1Ty(global_context));

    StructType *intftype = StructType::create(global_context, ArrayRef<Type*>(elements), getName());*/
    StructType *intftype = StructType::create(global_context, getName());
    dt = buildTypes->addDataType(this, intftype);
    buildTypes->setInterface(dt, true);
    if (dt == BuildTypes::undefinedType) {
        yyerrorcpp("Type " + name + " alread defined.", this);
        yyerrorcpp(name + " was first defined here.", buildTypes->location(dt));
    }
}

Value *Interface::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

    // set function parameters
    for(Node *n : node_children) {
        FunctionDecl *fd = dynamic_cast<FunctionDecl*>(n);
        if (fd) {
            fd->setPrefixName(getName());
            fd->addThisArgument(dt);
            fd->generate(func, block, allocblock);
        }
    }

    return NULL;
}

bool Interface::validateImplementation(UserType *ut) {
    bool result = true;
    for(const auto & [key, func_decl] : getSymbols()) {
        auto symb = ut->findSymbol(key, false);
        FunctionImpl *fimpl = dynamic_cast<FunctionImpl*>(symb);
        if (!symb) {
            yyerrorcpp(string_format("Type %s doesn't implement %s.", ut->getName().c_str(),
                key.c_str()), ut);
            yywarncpp(string_format("%s is defined here.", key.c_str()), func_decl);
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
