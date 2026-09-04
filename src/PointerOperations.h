#pragma once

#include "Load.h"
#include "Node.h"
#include "semantic/Visitor.h"

class AddressOf: public Node {
public:
    AddressOf(Node *value, location_t loc): Node(loc) {
        addChild(value);
    }

    Node *value() const {
        return node_children[0];
    }

    virtual DataType getDataType() override;
    virtual Value *generate(FunctionImpl *func, BasicBlock *block,
        BasicBlock *allocblock) override;
    virtual Node *accept(Visitor& v) override {
        return v.visit(*this);
    }
};

class Dereference: public LoadBase {
public:
    Dereference(Node *pointer, location_t loc): LoadBase(loc) {
        addChild(pointer);
    }

    Node *pointer() const {
        return node_children[0];
    }

    virtual DataType getDataType() override;
    virtual Value *generate(FunctionImpl *func, BasicBlock *block,
        BasicBlock *allocblock) override;
    virtual Node *accept(Visitor& v) override {
        return v.visit(*this);
    }
};

class PointerStore: public Node {
public:
    PointerStore(Node *pointer, Node *value, location_t loc): Node(loc) {
        addChild(pointer);
        addChild(value);
    }

    Node *pointer() const {
        return node_children[0];
    }

    Node *value() const {
        return node_children[1];
    }

    void setValue(Node *value) {
        node_children[1] = value;
    }

    virtual DataType getDataType() override;
    virtual Value *generate(FunctionImpl *func, BasicBlock *block,
        BasicBlock *allocblock) override;
    virtual Node *accept(Visitor& v) override {
        return v.visit(*this);
    }
};

class NullPointer: public Node {
public:
    NullPointer(DataType pointerType, location_t loc): Node(loc) {
        dt = pointerType;
    }

    virtual Value *generate(FunctionImpl *func, BasicBlock *block,
        BasicBlock *allocblock) override;
};
