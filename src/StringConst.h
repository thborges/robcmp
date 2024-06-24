
#pragma once

#include "Array.h"
#include "HeaderGlobals.h"

class StringConst: public Array {
protected:
    string str;
public:
    StringConst(const string& name, const string& str, location_t loc);
    
    virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

    virtual DataType getDataType() override {
        if (dt == BuildTypes::undefinedType)
            dt = buildTypes->getArrayType(buildTypes->name(tchar), getLoc(), 1, true);
        return dt;
    }

    virtual DataType getElementDataType() override {
		return tchar;
	}

	virtual int getSize() const override {
		return str.size();
	}

    virtual Type *getLLVMType() override {
        return buildTypes->llvmType(dt);
    }

    virtual bool isConstExpr() override {
		return true;
	}
};
