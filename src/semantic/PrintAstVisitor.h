
#pragma once

#include "Node.h"
#include "RecursiveVisitor.h"

class PrintAstVisitor: public RecursiveVisitor {
protected:
	std::ostream& os;
public:
	PrintAstVisitor(std::ostream& _os);

	virtual Node* visit(Node& p) override;
	void visit_children(Node& n);
	bool before(Node& n) override;
	void after(Node& n) override;

	virtual Node* visit(Program& p) override;
	virtual Node* visit(Int8& n) override;
	virtual Node* visit(Int16& n) override;
	virtual Node* visit(Int32& n) override;

	const string getOperatorName(int op);
	virtual Node* visit(CmpOp& n) override;
	virtual Node* visit(BinaryOp& n) override;

	virtual Node* visit(Load& n) override;
	virtual Node* visit(Scalar& n) override;

	virtual Node* visit(NamedNode& n) override;
	virtual Node* visit(FunctionCall& n) override;
	virtual Node* visit(CoercionBase& n) override;

	virtual bool before(Program& p) override;
	virtual void after(Program& p) override;
};
