#pragma once

#include "Node.h"
#include "semantic/Visitor.h"

class BitCast: public Node {
private:
    Node *value;
    DataType destTy;

public:
	BitCast(Node *v, DataType dTy): Node(v->getLoc()), value(v), destTy(dTy) {
        addChild(v);
    }

    virtual DataType getDataType() override {
		return destTy;
	}

    virtual DataType getSourceType() {
        return value->getDataType();
    }

    virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

    virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
