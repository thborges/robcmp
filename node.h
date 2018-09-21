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
#include "bison.hpp"

extern int yyerror(const char *s);
extern int yylex();

// Program main module
extern Module *mainmodule;
extern BasicBlock *mainblock;
extern char* build_filename;
static LLVMContext global_context;

// symbol table
extern map<BasicBlock*, map<string, Value*>> tabelasym;

// arduino functions
extern Function *analogWrite;
extern Function *analogRead;
extern Function *delay;
extern Function *delayMicroseconds;

extern Function *init;
extern Function *print;
extern Function *i16div;

static int yyerrorcpp(const string& s) {
	string e = "semantic error, " + s;
	return yyerror(e.c_str());
}

static Value *search_symbol(const string& ident, BasicBlock *firstb = NULL, BasicBlock *secondb = NULL) {
	BasicBlock *blocks[] = {firstb, secondb, mainblock};
	for(BasicBlock *b : blocks) {
		if (b == NULL) 
			continue;
		auto blocksym = tabelasym[b];
		auto var = blocksym.find(ident);
		if (var != blocksym.end())
			return var->second;
	}
	return NULL;
}


class Node {
public:
	virtual bool isFunctionDecl() { return false; }
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) = 0;
	virtual ~Node() {}
};

class Int8: public Node {
private:
	char number;
public:
	Int8(char n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantInt::get(Type::getInt8Ty(global_context), number);
	}
};

class Int16: public Node {
private:
	short number;
public:
	Int16(short n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantInt::get(Type::getInt16Ty(global_context), number);
	}
};

class Int32: public Node {
private:
	int number;
public:
	Int32(int n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantInt::get(Type::getInt32Ty(global_context), number);
	}
};

class Float: public Node {
private:
	float number;
public:
	Float(float n): number(n) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantFP::get(Type::getFloatTy(global_context), number);
	}
};

class String: public Node {
private:
	string str;
public:
	String(const char *s): str(s) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return ConstantDataArray::getString(global_context, str, true);;
	}
};

class Load: public Node {
private:
	string ident;
public:
	Load(const char *i): ident(i) {}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *sym = search_symbol(ident, allocblock, block);	
		if (sym == NULL) {
			yyerrorcpp("Variable " + ident + " not defined.");
			return NULL;
		}
		LoadInst *ret = new LoadInst(sym, ident, false, block);
		return ret;
	}
};

class Variable: public Node {
private:
	string name;
	Node *expr;
public:
	Variable(const char *n, Node *e) : name(n), expr(e) { }

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value
		Value *exprv = expr->generate(func, block, allocblock);

		Value *leftv = search_symbol(name, allocblock, block);	
		if (leftv == NULL) {
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
			tabelasym[allocblock][name] = leftv; 
		}

		auto nvalue = exprv;
		if (leftv->getType()->getPointerElementType()->isIntegerTy() && 
			exprv->getType()->isFloatTy()) {
			nvalue = new FPToSIInst(exprv, leftv->getType()->getPointerElementType(), 
				"truncistore", block);
		}
		StoreInst *ret = new StoreInst(nvalue, leftv, false, block);
		return ret;

	}
};

class InPort: public Node {
private:
	string port;
public:
	InPort(const char *p): port(p) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;
		
		Int8 prt(atoi(port.c_str()));
		args.push_back(prt.generate(func, block, allocblock));
		
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
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;
		
		Int8 prt(atoi(port.c_str()));
		args.push_back(prt.generate(func, block, allocblock));

		Value *value = expr->generate(func, block, allocblock);
		Value *nvalue = value;
		if (value->getType()->isFloatTy())
			nvalue = new FPToSIInst(value, Type::getInt16Ty(global_context), "trunci", block);

		args.push_back(nvalue);
		//Value *int8v = new TruncInst(value, Type::getInt8Ty(global_context), "", block);
		//args.push_back(int8v);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(analogWrite, argsRef, "", block);
	}
};

class Delay: public Node {
private:
	Node *ms;
public:
	Delay (Node *mseg) : ms(mseg) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *msv = ms->generate(func, block, allocblock);
		Value *msv32 = new SExtInst(msv, Type::getInt32Ty(global_context), "conv", block);

		vector<Value*> args;
		args.push_back(msv32);
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(delay, argsRef, "", block);
	}
};

class BinaryOp: public Node {
private:
	int op;
	Node *lhsn;
	Node *rhsn;
public:
	BinaryOp (Node *l, int op, Node *r) : lhsn(l), rhsn(r) {
		this->op =op;
	}

	Instruction *logical_operator(enum Instruction::BinaryOps op, 
		Function *func, BasicBlock *block, BasicBlock *allocblock) {
	
		Value *lhs = lhsn->generate(func, block, allocblock);
		Value *rhs = rhsn->generate(func, block, allocblock);
		return BinaryOperator::Create(op, lhs, rhs, "logicop", block);
	}

	Instruction *binary_operator(enum Instruction::BinaryOps opint, 
		enum Instruction::BinaryOps opflt, Function *func, BasicBlock *block, BasicBlock *allocblock) {

		Value *lhs = lhsn->generate(func, block, allocblock);
		Value *rhs = rhsn->generate(func, block, allocblock);

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

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		switch (op) {
			case '+' : return binary_operator(Instruction::Add, Instruction::FAdd, func, block, allocblock);
			case '-' : return binary_operator(Instruction::Sub, Instruction::FSub, func, block, allocblock);
			case '*' : return binary_operator(Instruction::Mul, Instruction::FMul, func, block, allocblock);
			case '/' : return binary_operator(Instruction::SDiv, Instruction::FDiv, func, block, allocblock);
			case '%' : return binary_operator(Instruction::SRem, Instruction::SRem, func, block, allocblock);
			case TOK_AND : return logical_operator(BinaryOperator::And, func, block, allocblock);
			case TOK_OR  : return logical_operator(BinaryOperator::Or, func, block, allocblock);
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
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		CmpInst::Predicate predicate; 

		Value *lexp = lexpn->generate(func, block, allocblock);
		Value *rexp = rexpn->generate(func, block, allocblock);

		Type *Ty1 = lexp->getType();
		Type *Ty2 = rexp->getType();
		int isFCmp = !Ty1->isIntegerTy() || !Ty2->isIntegerTy();
		if (isFCmp) {
			if (Ty1->isIntegerTy())
				lexp = new SIToFPInst(lexp, Type::getFloatTy(global_context), "", block);
			if (Ty2->isIntegerTy())
				rexp = new SIToFPInst(rexp, Type::getFloatTy(global_context), "", block);
		}

		if (op == EQ_OP)	  predicate = isFCmp ? FCmpInst::FCMP_OEQ : ICmpInst::ICMP_EQ;
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
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		return node->generate(func, block, allocblock);
	}
};

class If: public Node {
private:
	Node *expr;
	Node *thenst;
	Node *elsest;
public:
	If (Node *e, Node *tst, Node *est) : expr(e), thenst(tst), elsest(est) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *exprv = expr->generate(func, block, allocblock);

		BasicBlock *thenb = BasicBlock::Create(global_context, "if_then", func, 0);
		Value *thennewb = thenst->generate(func, thenb, allocblock);

		Value *elsenewb = NULL;
		BasicBlock *elseb = BasicBlock::Create(global_context, "if_else", func, 0);
		if (elsest != 0) {
			elsenewb = elsest->generate(func, elseb, allocblock);
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
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		BasicBlock *condwhile = BasicBlock::Create(global_context, "while_cond", func, 0);
		Value *exprv = expr->generate(func, condwhile, allocblock);

		BasicBlock *bodywhile = BasicBlock::Create(global_context, "while_body", func, 0);
		
		// alloc instructions inside bodywhile should go to block to prevent repeatedly allocation
		Value *newb = stmts->generate(func, bodywhile, block); 

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

class AttachInterrupt: public Node {
private:
	string fname;
	int port;
	int event;
	static Function *fattach;
public:
	AttachInterrupt(int _port, string _fname, int _event) {
		this->fname = _fname;
		this->port = _port;
		this->event = _event;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

		Function *cfunc = (Function*)search_symbol(fname);
		if (cfunc == NULL) {
			yyerrorcpp("Function " + fname + " not defined.");
			return NULL;
		}

		// called func type (the function that is attached to interruption)
		std::vector<Type*> arg_types;
		arg_types.push_back(Type::getVoidTy(global_context));
		FunctionType *fcalledtype = FunctionType::get(Type::getVoidTy(global_context),
			arg_types, false);
		
		// setup arduino attachInterrupt function
		if (!fattach) {
			arg_types.clear();
			arg_types.push_back(Type::getInt8Ty(global_context));
			arg_types.push_back(fcalledtype->getPointerTo());
			arg_types.push_back(Type::getInt16Ty(global_context));

			FunctionType *ftype = FunctionType::get(Type::getVoidTy(global_context),
				ArrayRef<Type*>(arg_types), false);

			fattach = Function::Create(ftype, Function::ExternalLinkage, "attachInterrupt", mainmodule);
			fattach->setCallingConv(CallingConv::C);
		}

		vector<Value*> args;
		args.push_back(ConstantInt::get(Type::getInt8Ty(global_context), port));
		args.push_back(cfunc);
		args.push_back(ConstantInt::get(Type::getInt16Ty(global_context), event));

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(fattach, argsRef, "", block);
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

	void prepend(Node *s) {
		// put after function declarations
		auto iterator = stmts.begin();
		while (iterator != stmts.end()) {
			if (!(*iterator)->isFunctionDecl())
				break;
			else
				iterator = std::next(iterator);
		}
		stmts.insert(iterator, s);
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		for(Node *n: stmts) {
			Value *b = n->generate(func, block, allocblock);
			if (b && b->getValueID() == Value::BasicBlockVal) 
				block = (BasicBlock*)b;
		}
		return block;
	}
};

class FunctionDecl: public Node {
private:
	Node *stmts;
	string name;
public:
	FunctionDecl(string name, Node *stmts) {
		this->name = name;
		this->stmts = stmts;
	}
	
	bool isFunctionDecl() {
		return true;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

		Value *sym = search_symbol(name);
		if (sym != NULL) {
			yyerrorcpp("Function " + name + " already defined.");
			return NULL;
		}

		BasicBlock *fblock = BasicBlock::Create(global_context, "entry");
		stmts->generate(func, fblock, fblock);

		TerminatorInst *term = fblock->getTerminator();
		Type *ttype = Type::getInt16Ty(global_context);
		if (term != NULL)
			ttype = fblock->getTerminator()->getType();
	
		std::vector<Type*> arg_types;
		FunctionType *ftype = FunctionType::get(ttype, ArrayRef<Type*>(arg_types), false);

		Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, name, mainmodule);
		nfunc->setCallingConv(CallingConv::C);
		//nfunc->setDoesNotReturn();

		fblock->insertInto(nfunc, 0);

		tabelasym[mainblock][name] = nfunc;
		return nfunc;
	}
};

class FunctionCall: public Node {
private:
	string name;
public:
	FunctionCall(string name) {
		this->name = name;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Function *cfunc = (Function*)search_symbol(name);
		if (cfunc == NULL) {
			yyerrorcpp("Function " + name + " not defined.");
			return NULL;
		}

		vector<Value*> args;
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(cfunc, argsRef, "", block);
	}
};

class Return: public Node {
private:
	Node *node;
public:
	Return(Node *n) {
		this->node = n;
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		IRBuilder<> builder(block);
		Value *ret = node->generate(func, block, allocblock);
		return builder.CreateRet(ret);
	}
};

class Print: public Node {
private:
	Node *expr;
public:
	Print(Node *e) : expr(e) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;

		Value *lexp = expr->generate(func, block, allocblock);
		char cty1 = -1;
		if (lexp != NULL) {
			Type *ty1 = lexp->getType();
			if (ty1->isIntegerTy())
				cty1 = 0;
			else if (ty1->isFloatTy())
				cty1 = 1;
			else if (ty1->isArrayTy())
				cty1 = 2;
		}
		if (cty1 == -1) {
			yyerrorcpp("Type not supported by print.");
			return NULL;
		}

		Int8 prt(cty1);
		args.push_back(prt.generate(func, block, allocblock));
		
		AllocaInst *ptr_aux = new AllocaInst(lexp->getType(), 0, "", allocblock);
		/*StoreInst *st = */ new StoreInst(lexp, ptr_aux, false, block);
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

		// analogWrite or digitalWrite
		arg_types.clear();
		arg_types.push_back(Type::getInt8Ty(global_context));
		arg_types.push_back(Type::getInt16Ty(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		analogWrite = Function::Create(ftype, Function::ExternalLinkage, "analogWrite", mainmodule);

		// digitalWrite instead
		/*arg_types.clear();
		arg_types.push_back(Type::getInt8Ty(global_context));
		arg_types.push_back(Type::getInt8Ty(global_context));
		ftype = FunctionType::get(Type::getVoidTy(global_context),
			ArrayRef<Type*>(arg_types), false);
		analogWrite = Function::Create(ftype, Function::ExternalLinkage, "digitalWrite", mainmodule);
		*/

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
		
		// init
		ftype = FunctionType::get(Type::getVoidTy(global_context), false);
		init = Function::Create(ftype, Function::ExternalLinkage, "init", mainmodule);
		init->setCallingConv(CallingConv::C);
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

		mainblock = BasicBlock::Create(global_context, "entry", mainfunc, 0);

		declara_auxiliary_c_funcs();

		// call Arduino init
		#ifdef ENABLE_ARDUINO
		std::vector<Value*> args;
		ArrayRef<Value*> argsRef(args);
		/*CallInst *call =*/ CallInst::Create(init, argsRef, "", mainblock);
		#endif

		// generate the program!
		Value *b = n->generate(mainfunc, mainblock, mainblock);
		if (b->getValueID() == Value::BasicBlockVal)  {
			mainblock = (BasicBlock*)b;
		}

		Int16 ret(0);
		Value *retv = ret.generate(mainfunc, mainblock, mainblock);
		ReturnInst::Create(global_context, retv, mainblock);
	}
};

/*
class _: public Node {
private:
public:
	_ () {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	}
};
*/

#endif

