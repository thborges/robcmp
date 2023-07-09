#ifndef __STMTS_H__
#define __STMTS_H__
#include "Node.h"

class Stmts: public Node {
private:
	std::vector<Node *> stmts;
public:
	Stmts(Node *s);

	virtual std::vector<Node *> const& children() const override;

	void append(Node *s);

	void prepend(Node *s);

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
};

#endif
