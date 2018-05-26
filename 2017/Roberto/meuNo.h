#include "node.h"

class Coord: public Node {
private:
	Int8 *coordX,*coordY;
public:
	Coord(Int8* x, Int8* y): coordX(x), coordY(y) {}
	Value *generate(Function *func, BasicBlock *block) {
         coordX->generate(func, block);
		return coordY->generate(func, block);
        
	}

    Int8* getCoordX()
    {
        return coordX;
    }
    Int8* getCoordY(){
        return coordY;
    }
};

class LinearMoveRet: public Node {
private:
	Node *x;
	Node *y;
	Node *z;
    Node *alt;
    Node *base;
public:
	LinearMove(Node *_z): x(NULL), y(NULL), z(_z) {}
	LinearMove(Node *_x, Node *_y) : x(_x), y(_y), z(NULL)  {}
	LinearMove(Node *_x, Node *_y, Node *_z) : x(_x), y(_y), z(_z)  {}
    //Logico da base do retangulo com a Altura, TODO
	Value *generate(Function *func, BasicBlock *block) {
		Value *myx, *myy, *myz;
		Value *auxfloat = Float(-1).generate(func, block);

		myx = myy = myz = auxfloat;
		if (x)
			myx = x->generate(func, block);
		if (y)
			myy = y->generate(func, block);
		if (z)
			myz = z->generate(func, block);

		vector<Value*> args;
		args.push_back(myx);
		args.push_back(myy);
		args.push_back(myz);
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(linearmove, argsRef, "", block);
	}	
};
class LinearMoveQuad: public Node {
private:
	Node *x;
	Node *y;
	Node *z;
    Node *lado;
public:
	LinearMove(Node *_z): x(NULL), y(NULL), z(_z) {}
	LinearMove(Node *_x, Node *_y) : x(_x), y(_y), z(NULL)  {}
	LinearMove(Node *_x, Node *_y, Node *_z) : x(_x), y(_y), z(_z)  {}
	Value *generate(Function *func, BasicBlock *block) {
		Value *myx, *myy, *myz;
		Value *auxfloat = Float(-1).generate(func, block);

		myx = myy = myz = auxfloat;
		if (x)
			myx = x->generate(func, block);
		if (y)
			myy = y->generate(func, block);
		if (z)
			myz = z->generate(func, block);

		vector<Value*> args;
		args.push_back(myx);
		args.push_back(myy);
		args.push_back(myz);
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(linearmove, argsRef, "", block);
	}	
};