
#pragma once

#include "Node.h"
#include "UserType.h"
#include "Matrix.h"
#include "Array.h"
#include "UpdateArray.h"
#include "BinaryOp.h"
#include "CmpOp.h"
#include "Return.h"
#include "FunctionImpl.h"
#include "FunctionCall.h"
#include "Enum.h"
#include "Load.h"
#include "MemCopy.h"
#include "BitCast.h"
#include "semantic/Visitor.h"

class CoercionBase: public Node {
protected:
	Node *node;

public:
	CoercionBase(Node *n, DataType newDt): Node(n->getLoc()) {
        node = n;
		dt = newDt;
        addChild(n);
        setScope(n->getScope());
        n->setScope(this, true);
	}

	virtual bool isConstExpr() override {
		return node->isConstExpr();
	}
};

class ExpandFloat: public CoercionBase {
public:
    ExpandFloat(Node *n, DataType newDt): CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        return Builder->CreateFPExt(v, buildTypes->llvmType(dt), "fpext");
    }
};

class SExtInt: public CoercionBase {
public:
    SExtInt(Node *n, DataType newDt): CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        return Builder->CreateSExt(v, buildTypes->llvmType(dt), "sext");
    }
};

class ZExtInt: public CoercionBase {
public:
    ZExtInt(Node *n, DataType newDt): CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        if (!v) {
            yyerrorcpp("There is no value to cast from (zext) ", node);
            return NULL;
        } else {
            RobDbgInfo.emitLocation(this);
            Builder->SetInsertPoint(block);
            return Builder->CreateZExt(v, buildTypes->llvmType(dt), "zext");
        }
    }
};

class TruncInt: public CoercionBase {
public:
    TruncInt(Node *n, DataType newDt): CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        return Builder->CreateTrunc(v, buildTypes->llvmType(dt), "trunc");
    }
};

class ExtendFloat: public CoercionBase {
public:
    ExtendFloat(Node *n, DataType newDt): CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        return Builder->CreateFPExt(v, buildTypes->llvmType(dt), "fpext");
    }
};

class TruncFloat: public CoercionBase {
public:
    TruncFloat(Node *n, DataType newDt): CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        return Builder->CreateFPTrunc(v, buildTypes->llvmType(dt), "trunc");
    }
};

class FloatToInt: public CoercionBase {
public:
    FloatToInt(Node *n, DataType newDt):
        CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        if (buildTypes->isUnsignedDataType(dt))
            return Builder->CreateFPToUI(v, buildTypes->llvmType(dt), "fptoui");
        else
            return Builder->CreateFPToSI(v, buildTypes->llvmType(dt), "fptosi");
    }
};

class IntToFloat: public CoercionBase {
public:
    IntToFloat(Node *n, DataType newDt):
        CoercionBase(n, newDt) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        if (buildTypes->isUnsignedDataType(node->getDataType()))
            return Builder->CreateUIToFP(v, buildTypes->llvmType(dt), "uitofp");
        else
            return Builder->CreateSIToFP(v, buildTypes->llvmType(dt), "sitofp");
    }
};

class DeferPointer: public CoercionBase {
public:
    DeferPointer(Node *n):
        CoercionBase(n, n->getDataType()) {}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override {
        Value *v = node->generate(func, block, allocblock);
        RobDbgInfo.emitLocation(this);
        Builder->SetInsertPoint(block);
        return Builder->CreateLoad(buildTypes->llvmType(dt), v, false, "deref");
    }
};

class ForcedCast: public CoercionBase {
public:
    ForcedCast(Node *n, DataType newDt): CoercionBase(n, newDt) {}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};

class PropagateTypes: public Visitor {
protected:
    DataType currentFunctionDt = BuildTypes::undefinedType;

public:
	PropagateTypes() {}

    void propagateChildren(Node& n, std::function<void(Node&)> lambda = NULL);

    Node *getChild(Node& n, int i) {
        return n.node_children[i];
    }

    static bool isUndefined(Node *n, bool checkDefined = true) {
        DataType dt = n->getDataType();
        if (dt == BuildTypes::undefinedType || 
            checkDefined && !buildTypes->isDefined(dt)) {
            string name = n->getName();
            if (name != "")
                yyerrorcpp(string_format("The type of %s is undefined.", name.c_str()), n);
            else
                yyerrorcpp("The type of the expression is undefined.", n);
            return true;
        }
        return false;
    }

    static Node *coerceTo(Node *n, const DataType destTy, bool warns = true);
    static Node *coerceToUserTypes(Node *n, const DataType destTy);
    DataType coerceArithOrCmp(Node& n, Node *left, Node *right);

    virtual Node* visit(Node& n) override {
        propagateChildren(n);
        return NULL;
    }

    virtual Node* visit(CmpOp& n) override;
    virtual Node* visit(BinaryOp& n) override;

    virtual Node* visit(Variable& n) override;
    virtual Node* visit(Scalar& n) override;
    virtual Node* visit(Load& n) override;
    virtual Node* visit(MemCopy& n) override;

    virtual Node* visit(Array& n) override;
    virtual Node* visit(Matrix& n) override;
    virtual Node* visit(UpdateArray& n) override;

    virtual Node* visit(UserType &n) override;
    virtual Node* visit(Enum &n) override;

    virtual Node* visit(Return& n) override;
    virtual Node* visit(FunctionImpl& n) override;
    virtual Node* visit(FunctionCall& n) override;

    virtual Node* visit(BitCast& n) override;
};
