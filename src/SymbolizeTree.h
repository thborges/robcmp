
#pragma once

#include "Node.h"
#include "Visitor.h"
#include "UserType.h"
#include "Matrix.h"
#include "Array.h"
#include "FunctionImpl.h"
#include "Scalar.h"
#include "Load.h"
#include "FunctionCall.h"
#include "ConstructorCall.h"
#include "MemCopy.h"
#include "Enum.h"

class SymbolizeTree: public Visitor {
public:
	SymbolizeTree() {}

    virtual Node* visit(Node& n) override {
        for(auto* c : n.children()) {
            c->setScope(&n);
            if (c->hasName()) {
                //fprintf(stderr, "%s\n", c->getName().c_str());
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
	    for(MatrixElement *i: n.getElements()) {
			for(ArrayElement *e: i->array->getElements()) {
                e->value->setScope(&n);
                e->value->accept(*this);
            }
        }
        return NULL;
    }

    virtual Node* visit(FunctionCall& n) override {
	    for(Node *p: n.getParameters()) {
            p->setScope(&n);
            p->accept(*this);
        }
        return NULL;
    }

    virtual Node* visit(Enum &n) override {
        visit((Node&)n);
        n.getDataType();
        return NULL;
    }
};
