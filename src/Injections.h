
#pragma once

#include <SourceLocation.h>

enum BindScope {bs_singleton, bs_transient};

struct Injection {
    string bind;
    string to;
    string singletonName;
    BindScope scope;
    SourceLocation loc;
    
    Injection(const string& bind, const string& to,
        BindScope scope, const SourceLocation& loc): loc(loc) {
        this->bind = bind;
        this->to = to;
        this->scope = scope;
        if (this->scope == bs_singleton)
            this->singletonName = "__var_injection_for_" + bind;
    }
};
