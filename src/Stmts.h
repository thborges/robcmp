#ifndef __STMTS_H__
#define __STMTS_H__
#include "Node.h"

class Stmts: public Node {
private:
	std::vector<Node *> stmts;
public:
	Stmts(Node *s) {
		this->stmts.push_back(s);
	}

	void append(Node *s);

	void prepend(Node *s);

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
