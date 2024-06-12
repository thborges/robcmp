
#include "Enum.h"
#include "Int8.h"
#include "NamedConst.h"

void Enum::createDataType() {
    if (children().size() > 256) {
        yyerrorcpp("Maximum number of elements for enum type was reached (256).", this);
        return;
    }

    dt = buildTypes->getType(name);
    if (dt != BuildTypes::undefinedType && buildTypes->isDefined(dt)) {
        yyerrorcpp("Type " + name + " alread defined.", this);
        yyerrorcpp(name + " was first defined here.", buildTypes->location(dt));
        return;
    }

    /* set enum items values
     *   enum A {B=1, C, D, E, F=10, G, H=127, I} => C=2, D=3 ... G=11 ... I=-128
     *   enum B {C=3, D=2, E, F} => E=4, F=5
     */
    uint8_t v = 0;
    map<uint8_t, Node*> values;
    for(Node *n : children()) {
        NamedConst *nc = (NamedConst*)n;
        Node *nv = nc->getValue();
        if (nv) {
            if (Int8 *i8 = dynamic_cast<Int8*>(nv))
                v = i8->getNumber();
            else if (UInt8 *ui8 = dynamic_cast<UInt8*>(nv))
                v = ui8->getNumber();

            if (values.count(v) == 1) {
                yyerrorcpp(string_format("Value %d alread taken for %s.", 
                    v, values[v]->getName().c_str()), nc);
            } else {
                values[v] = nc;
            }
        } else {
            while (values.count(v) == 1)
                v++;
            nc->setValue(new UInt8(v, nc->getLoc()));
            values[v] = nc;
        }
    }

    dt = buildTypes->addDataType(this, buildTypes->llvmType(tint8), 
        buildTypes->bitWidth(tint8), true);

    for(Node *n : children()) {
        n->setDataType(dt);
    }
}

Value* Enum::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    getDataType();
    return NULL;
}

DataType Enum::getDataType() {
    if (dt == BuildTypes::undefinedType)
        createDataType();
    return dt;
}