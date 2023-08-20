
#include "UserType.h"
#include "Interface.h"
#include "FunctionImpl.h"
#include "FunctionParams.h"
#include "FunctionCall.h"
#include "ParamsCall.h"
#include "Program.h"
#include "Visitor.h"
#include "Enum.h"
#include "Load.h"
#include "BackLLVM.h"

class ParentScalar: public Scalar {
public:
    ParentScalar(DataType parentDt) : Scalar("parent", new Load("#parent")) {
        expr->setScope(this);
        dt = parentDt;
        pointer = pm_pointer;
    }
    virtual DataType getDataType() override {
		return dt;
	}
    virtual Type* getLLVMType() override {
        return PointerType::get(global_context, dataAddrSpace);
    }
};

bool UserType::createDataType() {
    
    if (dt != BuildTypes::undefinedType)
        return true;
    else {
        // create an undefined type to use in recursive subtypes
        dt = buildTypes->getType(getName(), true);
    }

    std::vector<Type*> elements;

    int idx = 0;
    unsigned startBit = 0;
    vector<Variable*> addedVars;
    for(auto child : this->children()) {
        Variable *v = NULL;

        if (UserType *ut = dynamic_cast<UserType*>(child)) {
            // internal user type:
            // add a var in the internal type to store a reference to his parent
            ParentScalar *s = new ParentScalar(dt);
            s->setScope(ut);
            ut->addChild(s);
            ut->addSymbol(s);

            string varname = ut->getName();
            ut->setParent(this); // name changes after setting parent
            ut->createDataType();

            // create a new var in the parent to store the intf implementation
            FunctionCall *fc = new FunctionCall(ut->getName(), new ParamsCall());
            v = new Scalar(varname, fc);
            fc->setScope(v);
            v->setScope(this);
            addedVars.push_back(v);
            
            // fix the symbol table due to the renaming
            getScope()->addSymbol(ut);
            symbols[ut->getName()] = ut;
            symbols[v->getName()] = v;

        } else {
            v = dynamic_cast<Variable*>(child);
        }

        if (v) {
            if (v->getPointerMode() == pm_unknown)
                v->setPointer(pm_nopointer);
            
            Type *llvmType = v->getLLVMType();
            assert(llvmType && "Can not construct a type without its LLVM type.");
            if (!llvmType)
                return false;

            elements.push_back(llvmType);
            v->setGEPIndex(idx++);

            //FIXME: Fix for data alignment on non-packed structure/type
            startBits[v->getName()] = startBit;
            startBit += buildTypes->bitWidth(v->getDataType());
        }
    }
    bitWidth = startBit;

    for(auto a: addedVars) {
        addChild(a);
        addSymbol(a);
    }

    StructType *uttype = StructType::create(global_context, ArrayRef<Type*>(elements), getName());
    dt = buildTypes->addDataType(this, uttype, bitWidth);
    if (parent)
        buildTypes->setInternal(dt, true);

    if (dt == BuildTypes::undefinedType) {
        yyerrorcpp("Type " + name + " alread defined.", this);
        yyerrorcpp(name + " was first defined here.", buildTypes->location(dt));
        return false;
    }
    
    return true;
}

Value *UserType::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    
    if (!createDataType())
        return NULL;
    
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
        if (Variable *c = dynamic_cast<Variable*>(stmt)) {
            fields.push_back(c);
        }
    }

    // generate user types and enums
    for(auto & [key, stmt] : getSymbols()) {
        if (UserType *ut = dynamic_cast<UserType*>(stmt)) {
            ut->setDeclaration(declaration);
            ut->generate(func, block, allocblock);
        } else if (Enum *en = dynamic_cast<Enum*>(stmt)) {
            en->generate(func, block, allocblock);
        }
    }

    // generate init function/constructor
    FunctionParams *fp = new FunctionParams();
    FunctionImpl *finit = new FunctionImpl((DataType)tvoid, "init", fp, 
        std::move(fields), *this->getLoct(), true);
    finit->addThisArgument(dt);
    if (parent)
        finit->addParentArgument(parent->getDataType());
    finit->setUserTypeName(getName());
    finit->setExternal(declaration);
    finit->generate(func, block, allocblock);

    /* set function parameters before generate
     *  A function can call others that are still not generated
     *  and request their type info. So, here we set all needed
     *  info to pre-generate their type.
     */
    for(auto & [key, stmt] : getSymbols()) {
        if (FunctionImpl *f = dynamic_cast<FunctionImpl*>(stmt)) {
            f->setUserTypeName(getName());
            f->addThisArgument(dt);
            for(auto &field : fields)
                f->addSymbol(dynamic_cast<NamedNode*>(field));
            f->setExternal(declaration);
        }
    }

    // generate functions
    for(auto & [key, stmt] : getSymbols()) {
        if (FunctionImpl *f = dynamic_cast<FunctionImpl*>(stmt)) {
            f->generate(func, block, allocblock);
        }
    }

    addChild(finit);
    addSymbol(finit);
    return NULL;
}

void UserType::accept(Visitor& v) {
	v.visit(*this);
}

unsigned UserType::getFieldStartBit(Node *field) {
    return startBits[field->getName()];
}

const string UserType::getName() const {
    if (parent)
        return parent->getName() + "#" + NamedNode::getName();
    else
        return NamedNode::getName();
}

void UserType::addSymbol(NamedNode *nm) {
    // overrided here as UserType has its own scope
    symbols[nm->getName()] = nm;
}
