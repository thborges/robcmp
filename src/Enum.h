
#pragma once

#include "Node.h"

class Enum : public NamedNode {
private:
    void createDataType();

public:
    Enum(const string& name, vector<Node*> &&items): NamedNode(name, std::move(items)) {
    }

    virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
