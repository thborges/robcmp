#ifndef __PRINT_AST_VISITOR_H__
#define __PRINT_AST_VISITOR_H__

#include "Node.h"

class PrintAstVisitorNode: public RecursiveVisitor {
protected:
	std::ostream& os;
public:
	PrintAstVisitorNode(std::ostream& _os);
	virtual ~PrintAstVisitorNode();

	virtual void visit_children(Node const& n);
	virtual void visit(Node const& n) override;
	virtual bool before(Node const& n) override;
};

class PrintAstVisitor: public PrintAstVisitorNode {
public:
	PrintAstVisitor(std::ostream& _os);

	virtual void visit(Program const& p) override;
	virtual void visit(Int8 const& n) override;
	virtual void visit(Int16 const& n) override;
	virtual void visit(Int32 const& n) override;
	virtual void visit(While const& n) override;

	const string getOperatorName(int op);
	virtual void visit(CmpOp const& n) override;
	virtual void visit(BinaryOp const& n) override;

	virtual void visit(Load const& n) override;
	virtual void visit(Scalar const& n) override;
	virtual void visit(Delay const& n) override;
	virtual void visit(If const& n) override;

	virtual bool before(Program const& p) override;
	virtual void after(Program const& p) override;
};

#endif

