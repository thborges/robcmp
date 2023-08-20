
#include "Enum.h"
#include "Int8.h"
#include "NamedConst.h"

void Enum::createDataType() {
    if (children().size() > 256) {
        yyerrorcpp("Maximum number of elements for enum type was reached (256).", this);
        return;
    }

    /* set enum items values
     *   enum A {B=1, C, D, E, F=10, G, H=127, I} => C=2, D=3 ... G=11 ... I=-128
     *   enum B {C=3, D=2, E, F} => E=4, F=5
     */
    int8_t v = 0;
    map<int8_t, Node*> values;
    for(Node *n : children()) {
        NamedConst *nc = (NamedConst*)n;
        Int8 *i8 = dynamic_cast<Int8*>(nc->getValue());
        if (i8) {
            v = i8->getNumber();
            if (values.count(v) == 1) {
                yyerrorcpp(string_format("Value %d alread taken for %s.", 
                    v, values[v]->getName().c_str()), nc);
            } else {
                values[v] = nc;
            }
        } else {
            while (values.count(v) == 1)
                v++;
            nc->setValue(new Int8(v));
            values[v] = nc;
        }
    }

    dt = buildTypes->addDataType(this, buildTypes->llvmType(tint8), 
        buildTypes->bitWidth(tint8), true);
    if (dt == BuildTypes::undefinedType) {
        yyerrorcpp("Type " + name + " alread defined.", this);
        yyerrorcpp(name + " was first defined here.", buildTypes->location(dt));
        return;
    }

    for(Node *n : children()) {
        n->setDataType(dt);
    }
}

Value* Enum::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    createDataType();
    return NULL;
}