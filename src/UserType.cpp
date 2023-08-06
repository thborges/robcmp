
#include "UserType.h"
#include "Interface.h"
#include "FunctionImpl.h"
#include "FunctionParams.h"
#include "Program.h"
#include "Visitor.h"

void UserType::createDataType() {
    std::vector<Type*> elements;

    int idx = 0;
    for(auto nn : this->getSymbols()) {
        Scalar *s = dynamic_cast<Scalar*>(nn.second);
        if (s) {
            DataType sdt = s->getDataType();
            elements.push_back(buildTypes->llvmType(sdt));
            s->setGEPIndex(idx++);
        }
    }

    StructType *uttype = StructType::create(global_context, ArrayRef<Type*>(elements), name);
    dt = buildTypes->addDataType(this, uttype);
    if (dt == BuildTypes::undefinedType) {
        yyerrorcpp("Type " + name + " alread defined.", this);
        yyerrorcpp(name + " was first defined here.", buildTypes->location(dt));
        return;
    }
    
    /*printf("Type %s defined with:\n", name.c_str());
    for(const auto n : symbols) {
        printf("\t%s\n", n.first.c_str());
    }*/
}

Value *UserType::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    
    createDataType();
    
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

    // get vars
    vector<Node*> fields;
    for(auto & [key, stmt] : getSymbols()) {
        if (Scalar *c = dynamic_cast<Scalar*>(stmt)) {
            fields.push_back(c);
        }
    }
    
    // generate functions
    for(auto & [key, stmt] : getSymbols()) {
        if (FunctionImpl *f = dynamic_cast<FunctionImpl*>(stmt)) {
            f->setUserTypeName(name);
            f->addThisArgument(dt);
            for(auto &field : fields)
                f->addSymbol(dynamic_cast<NamedNode*>(field));
            f->generate(func, block, allocblock);
        }
    }

    FunctionParams *fp = new FunctionParams();
    FunctionImpl *finit = new FunctionImpl((DataType)tvoid, "init", fp, 
        std::move(fields), *this->getLoct(), true);
    finit->addThisArgument(dt);
    finit->setUserTypeName(name);
    addChild(finit);
    addSymbol(finit);
    return finit->generate(func, block, allocblock);
}

void UserType::accept(Visitor& v) {
	v.visit(*this);
}