#pragma once

#include "BuildTypes.h"
#include "Node.h"
#include "FunctionParams.h"
#include "Variable.h"
#include "Matrix.h"

class FunctionBase: public NamedNode {
protected:
	FunctionParams *parameters;
	Function *func = NULL;
	bool declaration = true;
	bool constructor = false;
	bool external = false;
	bool returnIsPointer = false;
	bool attrInline = false;
	DataType thisArgDt = BuildTypes::undefinedType;
	Value *thisArg = NULL;
	DataType parentArgDt = BuildTypes::undefinedType;
	Value *parentArg = NULL;
	string prefixName;

	bool validateAndGetArgsTypes(std::vector<Type*> &args);

public:
	FunctionBase(DataType dt, string name, FunctionParams *fp, location_t loc) :
		NamedNode(name, loc) {
		this->dt = dt;
		this->parameters = fp;
		addPseudoParameters();
	}

	FunctionBase(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts,
		location_t loc, bool constructor = false) :
		NamedNode(name, std::move(stmts), loc) {
		this->dt = dt;
		this->parameters = fp;
		this->constructor = constructor;
		addPseudoParameters();
	}

	void addPseudoParameters();

	FunctionParams& getParameters() {
		return *parameters;
	}

	virtual Value *getLLVMValue(Node *) override {
		return func;
	}

	virtual Function *getLLVMFunction() {
		return func;
	}

	unsigned getNumCodedParams() const {
		return parameters->getNumCodedParams();
	}

	bool isDeclaration() {
		return declaration;
	}

	void setDeclaration(bool d) {
		declaration = d;
	}

	bool isConstructor() {
		return constructor;
	}

	void setConstructor(bool c) {
		constructor = c;
	}

	void setExternal(bool e) {
		external = e;
	}

	void setInline(bool i) {
		attrInline = i;
	}

	bool isExternal() {
		return external;
	}

	void setReturnIsPointer(bool r) {
		returnIsPointer = r;
	}

	void addThisArgument(DataType dt);
	
	DataType getThisArgDt() const {
		return thisArgDt;
	}

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

	virtual bool needsParent() {
		return parentArg != NULL;
	}

	void setPrefixName(const string& prefix) {
		prefixName = prefix;
	}

	string getFinalName() {
		if (prefixName == "")
			return name;
		else
			return prefixName + ":" + name;
	}
};

class FunctionDecl: public FunctionBase {
public:
	FunctionDecl(DataType dt, string name, FunctionParams *fp, location_t loc) : 
		FunctionBase(dt, name, fp, loc) {
		declaration = true;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
