
#pragma once

#include "Node.h"
#include "ParamsCall.h"
#include "Identifier.h"
#include "Variable.h"

class FunctionCall: public Node {
private:
	Identifier ident;
	Node *symbol = NULL;
	Variable *leftValue = NULL;

public:
	FunctionCall(const string& name, ParamsCall *pc, location_t loc): Node(loc), ident(name, loc) {
		node_children.reserve(pc->getNumParams());
		node_children.insert(end(node_children), pc->getParameters().begin(),
			pc->getParameters().end());
		delete pc;
	}
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;

	virtual DataType getDataType() override;

	virtual void setLeftValue(Variable *symbol) override {
		leftValue = symbol;
	}

	std::vector<Node *>& getParameters() {
		return node_children;
	}

	Node* accept(Visitor& v) override;

	const string getName() const override {
		return ident.getFullName();
	}

	Identifier& getIdent() {
		return ident;
	}
};
