#ifndef __SCALAR_H__
#define __SCALAR_H__
#include "Node.h"
#include "Float.h"

class Scalar: public Node {
private:
	string name;
	Node *expr;
	bool isVolatile;
public:
	Scalar(const char *n, Node *e, bool volatile = false);

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;

	string getIdent() const { return name; };

	virtual void accept(Visitor& v) override;
};

#endif
