#ifndef __Matrix_H__
#define __Matrix_H__

class Matrix: public Node {
private:
	string name;
	MatrixElements *melements;
public:
	Matrix(const char *n, MatrixElements *me) : name(n), melements(me) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
