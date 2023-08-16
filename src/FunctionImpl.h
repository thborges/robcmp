
#pragma once

#include "Node.h"
#include "FunctionDecl.h"

class Visitor;

class FunctionImpl: public FunctionBase {
private:
	SourceLocation endfunction;
	Value *thisArg = NULL;
	DataType parentArgDt = BuildTypes::undefinedType;
	Value *parentArg = NULL;
	bool preGenerated = false;
	BasicBlock *falloc = NULL;
	BasicBlock *fblock = NULL;

	bool preGenerate();
	
public:
	FunctionImpl(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts, location_t ef,
		bool constructor = false);
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	DISubroutineType *getFunctionDIType();

	bool validateImplementation(FunctionDecl *decl);

	void addParentArgument(DataType dt);

	Value *getThisArg() const {
		return thisArg;
	}

	Value *getParentArg() const {
		return parentArg;
	}

	DataType getParentArgDt() const {
		return parentArgDt;
	}

	virtual bool needsParent() override {
		return parentArg != NULL;
	}

	virtual void accept(Visitor& v) override;

	virtual Value *getLLVMValue(Node *) override;
};
