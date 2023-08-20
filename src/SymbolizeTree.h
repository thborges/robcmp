
#pragma once

#include "Node.h"
#include "Visitor.h"
#include "UserType.h"
#include "Matrix.h"
#include "Array.h"
#include "FunctionImpl.h"
#include "Loop.h"
#include "While.h"
#include "FunctionCall.h"

class SymbolizeTree: public Visitor {
public:
	SymbolizeTree() {}

    virtual void visit(Node& n) override {
        for(auto& c : n.children()) {
            c->setScope(&n);
            if (c->hasName()) {
                //fprintf(stderr, "%s\n", c->getName().c_str());
		        n.addSymbol(dynamic_cast<NamedNode*>(c));
            }
        }
        for(auto& c : n.children()) {
            c->accept(*this);
        }
    }

    virtual void visit(Array& n) override {
        for(auto& c : n.children()) {
            if (c->hasName()) {
		        n.addSymbol(dynamic_cast<NamedNode*>(c));
            }
        }
        for(ArrayElement *e : n.getElements())
            e->value->setScope(&n);
    }

    virtual void visit(Matrix& n) override {
        for(auto& c : n.children()) {
            if (c->hasName()) {
		        n.addSymbol(dynamic_cast<NamedNode*>(c));
            }
        }
	    for(MatrixElement *i: n.getElements()) {
			for(ArrayElement *e: i->array->getElements()) {
                e->value->setScope(&n);
            }
        }
    }

    virtual void visit(FunctionCall& n) override {
	    for(Node *p: n.getParameters()) {
            p->setScope(&n);
            p->accept(*this);
        }
    }
};
