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

	void append(Node *s) {
		stmts.push_back(s);
	}

	void prepend(Node *s) {
		// put after function declarations
		auto last_func = stmts.begin();
		auto iterator = stmts.begin();
		while (iterator != stmts.end()) {
			if ((*iterator)->isFunctionDecl())
				last_func = iterator;
			iterator = std::next(iterator);
		}
		last_func = std::next(last_func);
		stmts.insert(last_func, s);
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		for(Node *n: stmts) {
			Value *b = n->generate(func, block, allocblock);
			if (b && b->getValueID() == Value::BasicBlockVal) 
				block = (BasicBlock*)b;
		}
		return block;
	}
};

#endif
