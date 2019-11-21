#ifndef __LOAD_MATRIX_H__
#define __LOAD_MATRIX_H__
#include "Node.h"

class LoadMatrix: public Node {
private:
	string ident;
	Node *position_1;
	Node *position_2;
public:
	LoadMatrix(const char *i, Node *pos_1, Node *pos_2): ident(i), position_1(pos_1), position_2(pos_2) {}

	Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
