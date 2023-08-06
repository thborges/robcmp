#pragma once

#include "Node.h"
#include "FunctionParams.h"
#include "Variable.h"

class FunctionBase: public NamedNode {
protected:
	FunctionParams *parameters;
	Function *func = NULL;
	bool declaration = true;

	bool validateAndGetArgsTypes(std::vector<Type*> &args);

public:
	FunctionBase(DataType dt, string name, FunctionParams *fp) : NamedNode(name) {
		this->dt = dt;
		this->parameters = fp;
	}

	FunctionBase(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts,
		bool constructor = false) :
		NamedNode(name, std::move(stmts), constructor) {
		this->dt = dt;
		this->parameters = fp;
	}

	FunctionParams& getParameters() {
		return *parameters;
	}

	virtual Value *getLLVMValue(Node *) override {
		return func;
	}

	virtual Function *getLLVMFunction() {
		return func;
	}

	unsigned getNumParams() const {
		return parameters->getNumParams();
	}

	bool isDeclaration() {
		return declaration;
	}
};

class FunctionDecl: public FunctionBase {
public:
	FunctionDecl(DataType dt, string name, FunctionParams *fp) : 
		FunctionBase(dt, name, fp) {
		declaration = true;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
