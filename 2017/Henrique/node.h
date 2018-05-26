#ifndef NODE_H
#define NODE_H

#define ENABLE_ARDUINO
#define ENABLE_PRINT

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/InlineAsm.h>

using namespace std;
using namespace llvm;

class Node;
class Stmts;
#include "sintatico.h"

extern int yyerror(const char *s);
extern int yylex();

// Program main module
extern Module *mainmodule;
extern char* build_filename;
static LLVMContext global_context;

// symbol table
extern map<string, AllocaInst*> tabelasym;
extern map<string, int> symexists;

// arduino functions
extern Function *analogWrite;
extern Function *analogRead;
extern Function *delay;
extern Function *delayMicroseconds;

extern Function *linearmove;
extern Function *arcmove;

extern Function *initf;
extern Function *print;
extern Function *i16div;

class Node {
public:
	virtual Value *generate(Function *func, BasicBlock *block) = 0;
	virtual ~Node() {}
};

class Int8: public Node {
private:
	char number;
public:
	Int8(char n): number(n) {}
	Value *generate(Function *func, BasicBlock *block) {
		return ConstantInt::get(Type::getInt8Ty(global_context), number);
	}
};

class Int16: public Node {
private:
	short number;
public:
	Int16(short n): number(n) {}
	Value *generate(Function *func, BasicBlock *block) {
		return ConstantInt::get(Type::getInt16Ty(global_context), number);
	}
};

class Int32: public Node {
private:
	int number;
public:
	Int32(int n): number(n) {}
	Value *generate(Function *func, BasicBlock *block) {
		return ConstantInt::get(Type::getInt32Ty(global_context), number);
	}
};

class Float: public Node {
private:
	float number;
public:
	Float(float n): number(n) {}
	Value *generate(Function *func, BasicBlock *block) {
		return ConstantFP::get(Type::getFloatTy(global_context), number);
	}
};

class String: public Node {
private:
	string str;
public:
	String(const char *s): str(s) {}	
	Value *generate(Function *func, BasicBlock *block) {
		return ConstantDataArray::getString(global_context, str, true);;
	}
};

class Load: public Node {
private:
	string ident;
public:
	Load(const char *i): ident(i) {
		auto var = symexists.find(ident);
		if (var == symexists.end())
			yyerror("Variable not declared:");
	}

	Value *generate(Function *func, BasicBlock *block) {
		LoadInst *ret = new LoadInst(tabelasym[ident], ident, false, block);
		return ret;
	}
};

class Variable: public Node {
private:
	string name;
	Node *expr;
public:
	Variable(const char *n, Node *e) : name(n), expr(e) {
		symexists[n] = 1; // variable exists!
	}

	Value *generate(Function *func, BasicBlock *block) {
		auto left = tabelasym.find(name);
		Value *leftv;
		Value *exprv = expr->generate(func, block);
		if (left == tabelasym.end()) {
			tabelasym[name] = new AllocaInst(exprv->getType(), name, block);
			leftv = tabelasym[name];
		}
		else
			leftv = left->second;

		StoreInst *ret = new StoreInst(exprv, leftv, false, block);
		return ret;

	}
};

class InPort: public Node {
private:
	string port;
public:
	InPort(const char *p): port(p) {}
	Value *generate(Function *func, BasicBlock *block) {
		vector<Value*> args;
		
		Int8 prt(atoi(port.c_str()));
		args.push_back(prt.generate(func, block));
		
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(analogRead, argsRef, "", block);
	}
};

class OutPort: public Node {
private:
	string port;
	Node *expr;
public:
	OutPort (const char *p, Node *e) : port(p), expr(e) {}
	Value *generate(Function *func, BasicBlock *block) {
		vector<Value*> args;
		
		Int8 prt(atoi(port.c_str()));
		args.push_back(prt.generate(func, block));

		Value *value = expr->generate(func, block);
		Value *nvalue = value;
		if (value->getType()->isFloatTy())
			nvalue = new FPToSIInst(value, Type::getInt16Ty(global_context), "trunci", block);

		//args.push_back(nvalue);
        Value *int8v = new TruncInst(value, Type::getInt8Ty(global_context), "", block);
        args.push_back(int8v);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(analogWrite, argsRef, "", block);
	}
};

class Delay: public Node {
private:
	Node *ms;
public:
	Delay (Node *mseg) : ms(mseg) {}
	Value *generate(Function *func, BasicBlock *block) {
		Value *msv = ms->generate(func, block);
		Value *msv32 = new SExtInst(msv, Type::getInt32Ty(global_context), "conv", block);

		vector<Value*> args;
		args.push_back(msv32);
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(delay, argsRef, "", block);
	}
};

class ArcMove: public Node {
private:
	Node *x;
	Node *y;
	Node *z;
	Node *i;
	Node *j;
public:
	ArcMove(Node *_x, Node *_y, Node *_z, Node *_i, Node *_j) : x(_x), y(_y), z(_z), i(_i), j(_j)  {}
	Value *generate(Function *func, BasicBlock *block) {
		Value *myx, *myy, *myz, *myi, *myj;
		Value *auxfloat = Float(-1).generate(func, block);

		myx = myy = myz = myi = myj = auxfloat;
		if (x)
			myx = x->generate(func, block);
		if (y)
			myy = y->generate(func, block);
		if (z)
			myz = z->generate(func, block);
		if (i)
			myi = i->generate(func, block);
		if (j)
			myj = j->generate(func, block);

		vector<Value*> args;
		args.push_back(myx);
		args.push_back(myy);
		args.push_back(myz);
		args.push_back(myi);
		args.push_back(myj);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(arcmove, argsRef, "", block);
	}	
};


class LinearMove: public Node {
private:
	Node *x;
	Node *y;
	Node *z;
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


class BinaryOp: public Node {
private:
	char op;
	Node *lhsn;
	Node *rhsn;
public:
	BinaryOp (Node *l, char op, Node *r) : lhsn(l), rhsn(r) {
		this->op =op;
	}
	Instruction *binary_operator(enum Instruction::BinaryOps opint, 
		enum Instruction::BinaryOps opflt, Function *func, BasicBlock *block) {

		Value *lhs = lhsn->generate(func, block);
		Value *rhs = rhsn->generate(func, block);

		Type *Ty1 = lhs->getType();
		Type *Ty2 = rhs->getType();

		if (Ty1->isIntegerTy() && Ty2->isIntegerTy()) {
			/*fallback SDiv disabled
			if (opint == Instruction::SDiv) {
				vector<Value*> args;
				args.push_back(lhs);
				args.push_back(rhs);
				ArrayRef<Value*> argsRef(args);
				return CallInst::Create(i16div, argsRef, "", block);
			}*/
			return BinaryOperator::Create(opint, lhs, rhs, "", block);
		}
		else {
			Value *flhs = lhs, *frhs = rhs;
			if (Ty1->isIntegerTy())
				flhs = new SIToFPInst(lhs, Type::getFloatTy(global_context), "castitof", block);
			if (Ty2->isIntegerTy())
				frhs = new SIToFPInst(rhs, Type::getFloatTy(global_context), "castitof", block);
			return BinaryOperator::Create(opflt, flhs, frhs, "binop", block);
		}
	}

	Value *generate(Function *func, BasicBlock *block) {
		switch (op) {
			case '+' : return binary_operator(Instruction::Add, Instruction::FAdd, func, block);
			case '-' : return binary_operator(Instruction::Sub, Instruction::FSub, func, block);
			case '*' : return binary_operator(Instruction::Mul, Instruction::FMul, func, block);
			case '/' : return binary_operator(Instruction::SDiv, Instruction::FDiv, func, block);
			default: return NULL;
		}
	}
};

class CmpOp: public Node {
private:
	Node *lexpn;
	Node *rexpn;
	int op;
public:
	CmpOp (Node *l, int op, Node *r) : lexpn(l), rexpn(r) {
		this->op = op;
	}
	Value *generate(Function *func, BasicBlock *block) {
		CmpInst::Predicate predicate; 

		Value *lexp = lexpn->generate(func, block);
		Value *rexp = rexpn->generate(func, block);

		Type *Ty1 = lexp->getType();
		Type *Ty2 = rexp->getType();
		int isFCmp = !Ty1->isIntegerTy() || !Ty2->isIntegerTy();
		if (isFCmp) {
			if (Ty1->isIntegerTy())
				lexp = new SIToFPInst(lexp, Type::getFloatTy(global_context), "", block);
			if (Ty2->isIntegerTy())
				rexp = new SIToFPInst(rexp, Type::getFloatTy(global_context), "", block);
		}

		if (op == EQ_OP)		predicate = isFCmp ? FCmpInst::FCMP_OEQ : ICmpInst::ICMP_EQ;
		else if (op == NE_OP) predicate = isFCmp ? FCmpInst::FCMP_UNE : ICmpInst::ICMP_NE;
		else if (op == GE_OP) predicate = isFCmp ? FCmpInst::FCMP_OGE : ICmpInst::ICMP_SGE;
		else if (op == LE_OP) predicate = isFCmp ? FCmpInst::FCMP_OLE : ICmpInst::ICMP_SLE;
		else if (op == GT_OP) predicate = isFCmp ? FCmpInst::FCMP_OGT : ICmpInst::ICMP_SGT;
		else if (op == LT_OP) predicate = isFCmp ? FCmpInst::FCMP_OLT : ICmpInst::ICMP_SLT;
		else {
			cerr << "Invalid logical operator" << op << endl;
			return NULL;
		}

		if (isFCmp)
			return new FCmpInst(*block, predicate, lexp, rexp, "cmpf");
		else {
			return new ICmpInst(*block, predicate, lexp, rexp, "cmpi");
		}
	}
};

class Capsule: public Node {
private:
	Node *node;
public:
	Capsule (Node *n) : node(n) {}
	Value *generate(Function *func, BasicBlock *block) {
		return node->generate(func, block);
	}
};

class If: public Node {
private:
	Node *expr;
	Node *thenst;
	Node *elsest;
public:
	If (Node *e, Node *tst, Node *est) : expr(e), thenst(tst), elsest(est) {}
	Value *generate(Function *func, BasicBlock *block) {
		Value *exprv = expr->generate(func, block);

		BasicBlock *thenb = BasicBlock::Create(global_context, "if_then", func, 0);
		Value *thennewb = thenst->generate(func, thenb);

		Value *elsenewb = NULL;
		BasicBlock *elseb = BasicBlock::Create(global_context, "if_else", func, 0);
		if (elsest != 0) {
			elsenewb = elsest->generate(func, elseb);
		}
	
		BranchInst::Create(thenb, elseb, exprv, block);

		BasicBlock *mergb = BasicBlock::Create(global_context, "if_cont", func, 0);
		
		if (thennewb->getValueID() == Value::BasicBlockVal) 
			BranchInst::Create(mergb, (BasicBlock*)thennewb);
		else
			BranchInst::Create(mergb, thenb);
		
		if (elsenewb && elsenewb->getValueID() == Value::BasicBlockVal) 
			BranchInst::Create(mergb, (BasicBlock*)elsenewb);
		else
			BranchInst::Create(mergb, elseb);

		return mergb;
	}
};

class While: public Node {
private:
	Node *expr;
	Node *stmts;
public:
	While(Node *e, Node *stms) : expr(e), stmts(stms) {}
	Value *generate(Function *func, BasicBlock *block) {
		BasicBlock *condwhile = BasicBlock::Create(global_context, "while_cond", func, 0);
		Value *exprv = expr->generate(func, condwhile);

		BasicBlock *bodywhile = BasicBlock::Create(global_context, "while_body", func, 0);
		Value *newb = stmts->generate(func, bodywhile);

		BasicBlock *endwhile = BasicBlock::Create(global_context, "while_end", func, 0);
	
		BranchInst::Create(condwhile, block);
		BranchInst::Create(bodywhile, endwhile, exprv, condwhile);
		
		if (newb->getValueID() == Value::BasicBlockVal)
			BranchInst::Create(condwhile, (BasicBlock*)newb);
		else
			BranchInst::Create(condwhile, bodywhile);

		return endwhile;
	}
};

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

	Value *generate(Function *func, BasicBlock *block) {
		for(Node *n: stmts) {
			Value *b = n->generate(func, block);
			if (b->getValueID() == Value::BasicBlockVal) 
				block = (BasicBlock*)b;
		}
		return block;
	}
};

class Print: public Node {
private:
	Node *expr;
public:
	Print(Node *e) : expr(e) {}
	Value *generate(Function *func, BasicBlock *block) {
		vector<Value*> args;

		Value *lexp = expr->generate(func, block);
		Type *ty1 = lexp->getType();
		char cty1 = 0;
		if (ty1->isIntegerTy())
			cty1 = 0;
		else if (ty1->isFloatTy())
			cty1 = 1;
		else if (ty1->isArrayTy())
			cty1 = 2;
		else
			yyerror("Type not supported by print.");

		Int8 prt(cty1);
		args.push_back(prt.generate(func, block));
		
		AllocaInst *ptr_aux = new AllocaInst(lexp->getType(), "", block);
		StoreInst *st = new StoreInst(lexp, ptr_aux, false, block);
		CastInst *cinst = new BitCastInst(ptr_aux, PointerType::get(IntegerType::get(global_context, 8), 0), "", block);
		args.push_back(cinst);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(print, argsRef, "", block);
	}
};

class Program {
public:
	Program() {}
	
	void declara_auxiliary_c_funcs() {
		std::vector<Type*> arg_types;
		FunctionType *ftype;

		#ifdef ENABLE_ARDUINO
		// analogRead
		arg_types.clear();
		arg_types.push_back(Type::getInt8Ty(global_context));
		ftype = FunctionType::get(Type::getInt16Ty(global_context),
			ArrayRef<Type*>(arg_types), false);
		analogRead = Function::Create(ftype, Function::ExternalLinkage, "analogRead", mainmodule);
		analogRead->setCallingConv(CallingConv::C);

		// analogWrite
		arg_types.clear();
		arg_types.push_back(Type::getInt8Ty(global_context));
		//arg_types.push_back(Type::getInt16Ty(global_context));
		arg_types.push_back(Type::getInt8Ty(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
//		analogWrite = Function::Create(ftype, Function::ExternalLinkage, "analogWrite", mainmodule);
		analogWrite = Function::Create(ftype, Function::ExternalLinkage, "digitalWrite", mainmodule);
		analogWrite->setCallingConv(CallingConv::C);

		// delay 
		arg_types.clear();
		arg_types.push_back(Type::getInt32Ty(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		delay = Function::Create(ftype, Function::ExternalLinkage, "delay", mainmodule);
		delay->setCallingConv(CallingConv::C);


		// delayMicroseconds
		arg_types.clear();
		arg_types.push_back(Type::getInt32Ty(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		delayMicroseconds = Function::Create(ftype, Function::ExternalLinkage, "delayMicroseconds", mainmodule);
		delayMicroseconds->setCallingConv(CallingConv::C);
	
		// LinearMove 
		arg_types.clear();
		arg_types.push_back(Type::getFloatTy(global_context));
		arg_types.push_back(Type::getFloatTy(global_context));
		arg_types.push_back(Type::getFloatTy(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		linearmove = Function::Create(ftype, Function::ExternalLinkage, "linear_move", mainmodule);
		linearmove->setCallingConv(CallingConv::C);

		// ArcMove 
		arg_types.clear();
		arg_types.push_back(Type::getFloatTy(global_context));
		arg_types.push_back(Type::getFloatTy(global_context));
		arg_types.push_back(Type::getFloatTy(global_context));
		arg_types.push_back(Type::getFloatTy(global_context));
		arg_types.push_back(Type::getFloatTy(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		arcmove = Function::Create(ftype, Function::ExternalLinkage, "arc_move", mainmodule);
		arcmove->setCallingConv(CallingConv::C);
	
		// init
		ftype = FunctionType::get(Type::getVoidTy(global_context), false);
		initf = Function::Create(ftype, Function::ExternalLinkage, "init", mainmodule);
		initf->setCallingConv(CallingConv::C);
		#endif

		#ifdef ENABLE_PRINT
		// print
		arg_types.clear();
		arg_types.push_back(Type::getInt8Ty(global_context));
		arg_types.push_back(PointerType::get(IntegerType::get(global_context, 8), 0));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		print = Function::Create(ftype, Function::ExternalLinkage, "print", mainmodule);
		print->setCallingConv(CallingConv::C);
		#endif

		/* Not necessary anymore. Stay as an example
		AttributeSet print_func_attrs;
		print_func_attrs = 
			print_func_attrs.addAttribute(global_context, AttributeSet::FunctionIndex, Attribute::NoUnwind)
							 .addAttribute(global_context, AttributeSet::FunctionIndex, Attribute::StackProtect)
							 .addAttribute(global_context, AttributeSet::FunctionIndex, Attribute::UWTable)
							 .addAttribute(global_context, 1, Attribute::ZExt);
		print->setAttributes(print_func_attrs); */

		// i16divse)
		/*arg_types.clear();
		arg_types.push_back(Type::getInt16Ty(global_context));
		arg_types.push_back(Type::getInt16Ty(global_context));
		ftype = FunctionType::get(Type::getInt16Ty(global_context),
			ArrayRef<Type*>(arg_types), false);
		i16div = Function::Create(ftype, Function::ExternalLinkage, "i16div", mainmodule);
		i16div->setCallingConv(CallingConv::C);*/
	}

	void generate(Node *n) {
		mainmodule = new Module(build_filename, global_context);
	
		FunctionType *ftype = FunctionType::get(Type::getInt16Ty(global_context),
			ArrayRef<Type*>(), false);
		Function *mainfunc = Function::Create(ftype,GlobalValue::ExternalLinkage, "main", mainmodule);

		BasicBlock *mainblock = BasicBlock::Create(global_context, "entry", mainfunc, 0);

		declara_auxiliary_c_funcs();

		// call Arduino init
		#ifdef ENABLE_ARDUINO
		std::vector<Value*> args;
		ArrayRef<Value*> argsRef(args);
		CallInst *call = CallInst::Create(initf, argsRef, "", mainblock);
		#endif

		// generate the program!
		Value *b = n->generate(mainfunc, mainblock);
		if (b->getValueID() == Value::BasicBlockVal)  {
			mainblock = (BasicBlock*)b;
		}

		Int16 ret(0);
		Value *retv = ret.generate(mainfunc, mainblock);
		ReturnInst::Create(global_context, retv, mainblock);
	}
};

/*
class _: public Node {
private:
public:
	_ () {}
	Value *generate(Function *func, BasicBlock *block) {
	}
};
*/



class Coord: public Node {

private: 
	Node *coordX, *coordY;

public: 
	Coord (Node* x, Node* y): coordX(x), coordY(y){}
	Value *generate (Function *func, BasicBlock *block){
	coordX->generate(func, block);
	return coordY->generate(func, block);}

Node* getCoordX()
     {
       return coordX;
     }

Node *getCoordY()
{
  return coordY;
}


};

#endif


