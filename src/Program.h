#ifndef __PROGRAM_H__
#define __PROGRAM_H__
#include "Node.h"

class Program : public Node {
private:
	Stmts *stmts;
public:
	Program(Stmts *stmts);
	
	void declara_auxiliary_c_funcs();

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
	void generate();
	
};

#endif
