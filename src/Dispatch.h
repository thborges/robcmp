
#pragma once

#include <map>
#include <set>
#include "BuildTypes.h"

//using namespace std;

class Dispatch {
protected:
    map<DataType, set<DataType>> dispatchHash;

public:
    void addDataTypeImplementation(DataType base, DataType impl);
    void generateDispatchFunctions(Node *scope);
};
