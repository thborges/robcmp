
#pragma once

#include "Node.h"
#include "UserType.h"
#include "Matrix.h"
#include "Array.h"
#include "UpdateArray.h"
#include "FunctionImpl.h"
#include "Scalar.h"
#include "Enum.h"
#include "semantic/Visitor.h"

class SymbolizeTree: public Visitor {
public:
	SymbolizeTree() {}

    virtual Node* visit(Node& n) override {
        for(auto* c : n.children()) {
            c->setScope(&n);
            if (c->hasName()) {
		        n.addSymbol(dynamic_cast<NamedNode*>(c));
            }
        }
        for(auto* c : n.children()) {
            c->accept(*this);
        }
        return NULL;
    }

    virtual Node* visit(Array& n) override {
        for(auto* c : n.children()) {
            if (c->hasName()) {
		        n.addSymbol(dynamic_cast<NamedNode*>(c));
            }
        }
        for(ArrayElement *e : n.getElements()) {
            e->value->setScope(&n);
            e->value->accept(*this);
        }
        return NULL;
    }

    virtual Node* visit(Matrix& n) override {
        for(auto* c : n.children()) {
            if (c->hasName()) {
		        n.addSymbol(dynamic_cast<NamedNode*>(c));
            }
        }
	    for(MatrixElement *i: n.getMatrixElements()) {
			for(ArrayElement *e: i->array->getElements()) {
                e->value->setScope(&n);
                e->value->accept(*this);
            }
        }
        return NULL;
    }

    virtual Node* visit(UpdateArray& n) override {
        for(auto* c : n.children()) {
            c->accept(*this);
        }
        // for operation assignment (eg. +=, -=, etc.), the indexes
        // are used twice, in the load and in the attribution.
        // so we check if they already has a scope before setting
        for(auto* c : n.children()) {
            if (!c->getScope()) {
                c->setScope(&n);
            }
        }
        return NULL;
    }

    virtual Node* visit(Enum &n) override {
        visit((Node&)n);
        n.getDataType();
        return NULL;
    }
};
