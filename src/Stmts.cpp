#include "Header.h"

	void Stmts::append(Node *s) {
		stmts.push_back(s);
	}

	void Stmts::prepend(Node *s) {
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

	Value *Stmts::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		for(Node *n: stmts) {
			Value *b = n->generate(func, block, allocblock);
			if (b && b->getValueID() == Value::BasicBlockVal) 
				block = (BasicBlock*)b;
		}
		return block;
	}
