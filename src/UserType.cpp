
#include "Header.h"

Value *UserType::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
    
    // semantic analysis
    for(auto n : implements) {
        Node *inode = findSymbol(n);
        Interface *intf = dynamic_cast<Interface*>(inode);
        if (!intf) {
            yyerrorcpp("Interface " + n + " not defined.", this);
            return NULL;
        }
        if (!intf->validateImplementation(this))
            return NULL;
    }

    for(const auto n : symbols) {
        printf("Will generate %s_%s function!\n", name.c_str(), n.first.c_str());
    }
    return NULL;
}
