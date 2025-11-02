
#pragma once

#include "Load.h"
#include <string>

using namespace std;

struct LeftValueData {
    string ident;
    location_t loc;
    LoadBase *value = NULL;
    LoadBase *stem = NULL;
};
