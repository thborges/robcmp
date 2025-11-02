
#pragma once
#include "Visitor.h"
#include "Injections.h"

class InjectionsBind: public Visitor {
    protected:
    public:
        InjectionsBind() {}
        virtual Node* visit(Node& n) override;
        virtual Node* visit(UserType& n) override;
        bool validate();
};
