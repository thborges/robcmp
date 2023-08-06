
#pragma once

#include "Node.h"
#include "FunctionDecl.h"

class Visitor;

class FunctionImpl: public FunctionBase {
private:
	SourceLocation endfunction;
	DataType thisArgDt = BuildTypes::undefinedType;
	Value *thisArg = NULL;
	string userTypeName;
	
public:
	FunctionImpl(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts, location_t ef,
		bool constructor = false);
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	DISubroutineType *getFunctionDIType();

	bool validateImplementation(FunctionDecl *decl);

	void addThisArgument(DataType dt);

	Value *getThisArg() const {
		return thisArg;
	}

	DataType getThisArgDt() const {
		return thisArgDt;
	}

	void setUserTypeName(const string& ut) {
		userTypeName = ut;
	}

	string getFinalName() {
		if (userTypeName == "")
			return name;
		else
			return userTypeName + "#" + name;
	}

	virtual void accept(Visitor& v) override;
	
};
