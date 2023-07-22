#include "Header.h"

void Stmts::append(Node *s) {
	node_children.push_back(s);
	if (s->hasName())
		update_names = true;
}

void Stmts::prepend(Node *s) {
	// put after function declarations
	auto last_func = node_children.begin();
	auto iterator = node_children.begin();
	while (iterator != node_children.end()) {
		if ((*iterator)->isFunctionDecl())
			last_func = iterator;
		iterator = next(iterator);
	}
	last_func = next(last_func);
	node_children.insert(last_func, s);
}

Value *Stmts::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	for(Node *n: node_children) {
		Value *b = n->generate(func, block, allocblock);
		if (b && b->getValueID() == Value::BasicBlockVal) 
			block = (BasicBlock*)b;
	}
	return block;
}
