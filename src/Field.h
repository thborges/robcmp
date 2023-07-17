
#pragma once

#include "Header.h"

typedef struct {
    LanguageDataType fieldDataType;
    char *fieldName;
    unsigned startBit;
    unsigned bitWidth;
} Field;

class Structure {
public:
    int nextBit;
    map<string, Field> fields;
};

class ComplexIdentifier {
public:
    vector<string> names;
};
