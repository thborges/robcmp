
#pragma once

#include "BuildTypes.h"
#include "HeaderGlobals.h"
#include "Node.h"

class UndefInit: public Node {
public:
    UndefInit(DataType dt, location_t loc): Node(loc) {
		this->dt = dt;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        return UndefValue::get(buildTypes->llvmType(dt));
    }

	virtual bool isConstExpr() override {
		return true;
	}
};
