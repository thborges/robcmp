
#pragma once

#include "Node.h"
#include "RecursiveVisitor.h"

class PrintAstVisitor: public RecursiveVisitor {
protected:
	std::ostream& os;
public:
	PrintAstVisitor(std::ostream& _os);

	virtual void visit(Node& p) override;
	void visit_children(Node& n);
	bool before(Node& n) override;
	void after(Node& n) override;

	virtual void visit(Program& p) override;
	virtual void visit(Int8& n) override;
	virtual void visit(Int16& n) override;
	virtual void visit(Int32& n) override;

	const string getOperatorName(int op);
	virtual void visit(CmpOp& n) override;
	virtual void visit(BinaryOp& n) override;

	virtual void visit(Load& n) override;
	virtual void visit(Scalar& n) override;

	virtual bool before(Program& p) override;
	virtual void after(Program& p) override;
};
