#pragma once

#include "Node.h"
#include "Load.h"
#include "semantic/Visitor.h"

class FieldAccess: public LoadBase {
private:
	string field;
	
public:
	FieldAccess(LoadBase *leftValue, const char* fieldName, location_t floc): 
        LoadBase(floc), field(fieldName) {
		this->leftValue = leftValue;
		node_children.push_back(leftValue);
	}
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;
	
	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}

	const string& getField() {
		return field;
	}
};
