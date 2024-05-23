
#pragma once

#include "Node.h"
#include "Identifier.h"

enum PointerMode {pm_unknown, pm_pointer, pm_nopointer};

class Variable: public NamedNode {
protected:
    Value *alloc = NULL;
    Identifier ident;
	int gepIndex = -1;
	enum PointerMode pointer = pm_unknown;

public:
    Variable(const string &name): NamedNode(name), ident(name) {}
	
	Variable(const string &name, DataType dt): NamedNode(name), ident(name) {
		this->dt = dt;
	}

    virtual Value* getLLVMValue(Node *stem) override;
	
    virtual void setGEPIndex(int idx) {
		gepIndex = idx;
	}

	int getGEPIndex() const {
		return gepIndex;
	}

	void setPointer(enum PointerMode v) {
		pointer = v;
	}

	enum PointerMode getPointerMode() {
		return pointer;
	}

	void setAlloca(Value *alloc) {
		this->alloc = alloc;
	}

};
