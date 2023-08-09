
#pragma once

#include "Node.h"
#include "ParamsCall.h"
#include "Identifier.h"

class FunctionCall: public Node {
private:
	Identifier ident;
	ParamsCall *parameters;
	Node *symbol = NULL;
	Value *leftValue = NULL;
	string leftName;

public:
	FunctionCall(const char *name, ParamsCall *pc): ident(name) {
		parameters = pc;
	}
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
	void loadFunctionStem(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);

	virtual DataType getDataType() override;

	virtual void setLeftValue(Value *lv, const string& name) override {
		leftValue = lv;
		leftName = name;
	}

	std::vector<Node *> const& getParameters() {
		return parameters->getParameters();
	}

	void accept(Visitor& v) override;
};
