
#pragma once

#include "BuildTypes.h"
#include "HeaderGlobals.h"
#include "Node.h"

class ZeroInit: public Node {
public:
	ZeroInit(DataType dt, location_t loc): Node(loc) {
		this->dt = dt;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
		return ConstantAggregateZero::get(buildTypes->llvmType(dt));
        //return ConstantPointerNull::get(PointerType::getUnqual(buildTypes->llvmType(dt)));
    }

	virtual bool isConstExpr() override {
		return true;
	}
};
