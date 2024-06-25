
#pragma once

#include <SourceLocation.h>

enum BindScope {bs_singleton, bs_transient};

struct Injection {
    string bind;
    string to;
    BindScope scope;
    SourceLocation loc;
    Injection(const string& bind, const string& to,
        BindScope scope, const SourceLocation& loc): loc(loc) {
        this->bind = bind;
        this->to = to;
        this->scope = scope;
    }
};
