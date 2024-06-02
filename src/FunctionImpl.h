
#pragma once

#include "Node.h"
#include "FunctionDecl.h"

class Visitor;

class FunctionImpl: public FunctionBase {
private:
	SourceLocation endfunction;
	bool preGenerated = false;
	BasicBlock *falloc = NULL;
	BasicBlock *fblock = NULL;

	DIFile *funit;
	DISubprogram *sp;
	bool preGenerate();
	
public:
	FunctionImpl(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts, location_t ef,
		bool constructor = false);
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	DISubroutineType *getFunctionDIType();

	bool validateImplementation(FunctionDecl *decl);

	virtual void accept(Visitor& v) override;

	virtual Value *getLLVMValue(Node *) override;

	virtual Function *getLLVMFunction() override {
		if (!preGenerated)
			preGenerate();
		return func;
	}

};
