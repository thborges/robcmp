#ifndef __SCALAR_H__
#define __SCALAR_H__
#include "Node.h"
#include "Float.h"

class Scalar: public Node {
private:
	string name;
	Node *expr;
	DataQualifier qualifier;
	ComplexIdentifier *complexIdent;
public:
	Scalar(const char *n, Node *e, DataQualifier qualifier = qnone);
	Scalar(ComplexIdentifier *ci, Node *e, DataQualifier qualifier = qnone);

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	string getIdent() const { return name; };

	virtual void accept(Visitor& v) override;
};

#endif
