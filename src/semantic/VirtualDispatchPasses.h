
#pragma once
#include "Visitor.h"

struct CompileTimeInject {
    FunctionCall *fc;
    string new_call;
};

class IdentifyVirtualDispatch: public Visitor {
    protected:
        vector<CompileTimeInject> identifiedCalls;
    public:
        IdentifyVirtualDispatch() {}
        void propagateChildren(Node& n);
        virtual Node* visit(Node& n) override;
        virtual Node* visit(FunctionCall& n) override;
        void applyIdentifiedChanges();
};
