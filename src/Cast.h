
#pragma once

#include "Header.h"

class Cast: public Node {
private:
    Node *expr;
    LanguageDataType dt;
public:
    Cast(LanguageDataType dt, Node *expr): dt(dt), expr(expr) {}
    virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
    virtual void accept(Visitor &v) override;
};
