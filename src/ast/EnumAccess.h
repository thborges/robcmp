#pragma once

#include "Node.h"
#include "Load.h"
#include "Enum.h"
#include "semantic/Visitor.h"

class EnumAccess: public LoadBase {
private:
	Enum *enumType;
    string enumItem;
	
public:
	EnumAccess(Enum *enumType, string enumItem) :
        LoadBase(enumType->getLoc()), enumType(enumType), enumItem(enumItem) {
		node_children.push_back(enumType);
	}
 
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        return enumType->findMember(enumItem)->generate(NULL, NULL, NULL);
    }

    virtual bool isConstExpr() override {
        return true;
    }

	virtual DataType getDataType() override {
        return enumType->getDataType();
    }

	virtual Node* accept(Visitor& v) override {
		return v.visit(*this);
	}
};
