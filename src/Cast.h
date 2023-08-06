
#pragma once

#include "Node.h"

class Cast: public Node {
private:
    Node *expr;
    
public:
    Cast(DataType dt, Node *expr): expr(expr) {
        this->dt = dt;
    }
    virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

};
