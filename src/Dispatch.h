
#pragma once

#include <map>
#include <set>
#include "BuildTypes.h"

//using namespace std;

class Dispatch {
protected:
    map<DataType, set<DataType>> dispatchHash;
    set<DataType> intfsInvoked;

public:
    void addDataTypeImplementation(DataType base, DataType impl);
    void addIntfInvocation(DataType intf);
    void generateDispatchFunctions(Node *scope);
    void notifyInterface(DataType intf);
    int getImplementationCount(DataType intf);

    bool isIntfInvoked(DataType intf) {
        return (intfsInvoked.find(intf) != intfsInvoked.end());
    }
};
