#ifndef __GRID_H__
#define __GRID_H__

class Grid: public Node {
private:
	string name;
	Node *expr;
public:
	Grid(const char *n, Node *e) : name(n), expr(e) { }

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);

};

#endif
