
#pragma once

#include "Node.h"
#include "Identifier.h"

class Variable: public NamedNode {
protected:
    Value *alloc = NULL;
    Identifier ident;
	int gepIndex = -1;

public:
    Variable(const string &name): NamedNode(name), ident(name) {}

    virtual Value* getLLVMValue(Node *stem) override;
	
    virtual void setGEPIndex(int idx) {
		gepIndex = idx;
	}

	int getGEPIndex() const {
		return gepIndex;
	}
};
