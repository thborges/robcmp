
#pragma once

#include "Node.h"

class Program : public Node {
public:

	Program(Stmts &&stmts): Node(std::move(stmts.node_children)) {}

	void declara_auxiliary_c_funcs();

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
	void generate();
	
};
