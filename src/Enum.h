
#pragma once

#include "Node.h"
#include "Visitor.h"

class Enum : public NamedNode {
private:
    void createDataType();

public:
    Enum(const string& name, vector<Node*> &&items, location_t loc):
        NamedNode(name, std::move(items), loc) {
    }

    virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

    virtual DataType getDataType() override;

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}
};
