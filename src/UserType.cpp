
#include "UserType.h"
#include "HeaderGlobals.h"
#include "Interface.h"
#include "FunctionImpl.h"
#include "FunctionDecl.h"
#include "FunctionParams.h"
#include "ConstructorCall.h"
#include "Variable.h"
#include "Visitor.h"
#include "Enum.h"
#include "Load.h"
#include "BackLLVM.h"

class ParentScalar: public Scalar {
public:
    ParentScalar(DataType parentDt, location_t loc) : Scalar("parent", new Load(":parent", loc)) {
        expr()->setScope(this);
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
            ParentScalar *s = new ParentScalar(dt, ut->getLoc());
            s->setScope(ut);
            ut->addChild(s);
            ut->addSymbol(s);

            string varname = ut->getName();
            ut->setParent(this); // name changes after setting parent
            ut->createDataType();

            // create a new var in the parent to store the intf implementation
            ConstructorCall *cc = new ConstructorCall(ut->getName(), ut->getLoc());
            v = new Scalar(varname, cc);
            cc->setScope(v);
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
            if (buildTypes->isInterface(v->getDataType())) {
                v->setPointer(pm_pointer);
                v->setPointerToPointer(true);
            } else if (v->getPointerMode() == pm_unknown)
                v->setPointer(pm_nopointer);
            
            DataType vdt = v->getDataType();
            if (!buildTypes->isDefined(vdt)) {
                Node *undeft = Identifier(buildTypes->name(vdt), getLoc()).getSymbol(this);
                UserType *undefut = dynamic_cast<UserType*>(undeft);
                if (undefut)
                    undefut->createDataType();
            }
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
    FunctionBase *finit;
    if (declaration) {
        finit = new FunctionDecl((DataType)tvoid, "init", fp, getLoc());
    } else {
        finit = new FunctionImpl((DataType)tvoid, "init", fp, 
            std::move(fields), getLoc(), getLoc(), true);
    }
    finit->addThisArgument(dt);
    if (parent)
        finit->addParentArgument(parent->getDataType());
    finit->setPrefixName(getName());
    finit->setExternal(declaration);
    finit->setConstructor(true);
    finit->generate(func, block, allocblock);

    /* set function parameters before generate
     *  A function can call others that are still not generated
     *  and request their type info. So, here we set all needed
     *  info to pre-generate their type.
     */
    for(auto & [key, stmt] : getSymbols()) {
        if (FunctionImpl *f = dynamic_cast<FunctionImpl*>(stmt)) {
            f->setPrefixName(getName());
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

Node* UserType::accept(Visitor& v) {
	return v.visit(*this);
}

unsigned UserType::getFieldStartBit(Node *field) {
    return startBits[field->getName()];
}

const string UserType::getName() const {
    if (parent)
        return parent->getName() + ":" + NamedNode::getName();
    else
        return NamedNode::getName();
}

void UserType::addSymbol(NamedNode *nm) {
    // overrided here as UserType has its own scope
    symbols[nm->getName()] = nm;
}
