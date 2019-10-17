#ifndef __Matrix_H__
#define __Matrix_H__

class Matrix: public Node {
private:
	string name;
	unsigned int size_l;
	unsigned int size_c;
	MatrixElements *arrays;
public:
	Matrix(const char *n, MatrixElements *me) : name(n), arrays(me) { }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock);
};

#endif
