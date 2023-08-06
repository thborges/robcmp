
#pragma once

#include "HeaderGlobals.h"
#include "Variable.h"

class Field : public Variable {
public:
    unsigned startBit;
    unsigned bitWidth;
    Field(const string& Name, DataType dt) : Variable(name) {
        setDataType(dt);
    }
};

class Structure {
public:
    int nextBit;
    map<string, Field*> fields;
};
