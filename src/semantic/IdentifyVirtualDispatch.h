
#pragma once
#include "Visitor.h"

class IdentifyVirtualDispatch: public Visitor {
    protected:
           
    public:
        IdentifyVirtualDispatch() {}
        void propagateChildren(Node& n);
        virtual Node* visit(Node& n) override;
        virtual Node* visit(FunctionCall& n) override;
};
