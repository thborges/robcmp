#pragma once

#include "BuildTypes.h"
#include "Node.h"
#include "FunctionParams.h"
#include "FunctionAttributes.h"

class FunctionBase: public NamedNode {
protected:
	FunctionParams *parameters;
	FunctionAttributes *attributes = new FunctionAttributes();
	Function *func = NULL;
	bool declaration = true;
	bool constructor = false;
	bool external = false;
	bool returnIsPointer = false;
	DataType thisArgDt = BuildTypes::undefinedType;
	Value *thisArg = NULL;
	DataType parentArgDt = BuildTypes::undefinedType;
	Value *parentArg = NULL;
	string prefixName;
	GlobalValue::LinkageTypes linkage = Function::ExternalLinkage;

	bool validateAndGetArgsTypes(std::vector<Type*> &args);
	void addFunctionAttributes(Function *f);

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

	~FunctionBase() {
		delete parameters;
		delete attributes;
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

	void setAttributes(FunctionAttributes *attributes) {
		delete this->attributes;
		this->attributes = attributes;
	}

	FunctionAttributes *getAttributes() {
		return attributes;
	}

	void setLinkage(GlobalValue::LinkageTypes l) {
		linkage = l;
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
