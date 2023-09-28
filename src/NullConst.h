
#pragma once

#include "BuildTypes.h"
#include "HeaderGlobals.h"
#include "Node.h"

class NullConst: public Node {
public:
	NullConst(DataType dt) {
		this->dt = dt;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        return ConstantPointerNull::get(PointerType::get(buildTypes->llvmType(dt), 0));
    }

	virtual bool isConstExpr() override {
		return true;
	}
};
