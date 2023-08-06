
#pragma once

#include "Node.h"

class BinaryOp;
class Capsule;
class CmpOp;
class Delay;
class Float;
class FunctionCall;
class FunctionDecl;
class FunctionImpl;
class FunctionBase;
class Matrix;
class If;
class InPort;
class Int16;
class Int32;
class Int64;
class Int8;
class Load;
class LoadArray;
class OutPort;
class Print;
class Program;
class Return;
class Scalar;
class StringConst;
class Array;
class While;
class Loop;
class UserType;
class Variable;
class NamedConst;
class LinearDataStructure;

#define VISITOR_DECLAREP(T, P) \
	virtual void visit(T& n) { visit((P&)n); } \
	virtual void after(T&) {} \
	virtual bool before(T&) { return false; }

#define VISITOR_DECLARE(T) \
	virtual void visit(T& n) { visit((Node&)n); } \
	virtual void after(T&) {} \
	virtual bool before(T&) { return false; }

#define VISITOR_VISIT(T) \
	void T::accept(Visitor& v) {\
		v.visit(*this);\
	}

class Visitor {
public:
	virtual void visit(Node&) { }
	virtual void after(Node&) {}
	virtual bool before(Node&) { return false; }

	VISITOR_DECLARE(NamedNode)
	VISITOR_DECLARE(BinaryOp)
	VISITOR_DECLARE(Capsule)
	VISITOR_DECLARE(CmpOp)
	VISITOR_DECLARE(Delay)
	VISITOR_DECLARE(Float)
	VISITOR_DECLARE(FunctionCall)
	VISITOR_DECLARE(If)
	VISITOR_DECLARE(InPort)
	VISITOR_DECLARE(Int16)
	VISITOR_DECLARE(Int32)
	VISITOR_DECLARE(Int8)
	VISITOR_DECLARE(Load)
	VISITOR_DECLARE(LoadArray)
	VISITOR_DECLARE(OutPort)
	VISITOR_DECLARE(Print)
	VISITOR_DECLARE(Program)
	VISITOR_DECLARE(Return)
	VISITOR_DECLARE(StringConst)
	VISITOR_DECLARE(While)
	VISITOR_DECLARE(Loop)
	VISITOR_DECLAREP(Scalar, Variable)
	VISITOR_DECLAREP(Variable, NamedNode)
	VISITOR_DECLAREP(NamedConst, NamedNode)
	VISITOR_DECLAREP(FunctionBase, NamedNode)
	VISITOR_DECLAREP(FunctionDecl, FunctionBase)
	VISITOR_DECLAREP(UserType, NamedNode)
	VISITOR_DECLAREP(FunctionImpl, FunctionBase)
	VISITOR_DECLAREP(LinearDataStructure, Variable)
	VISITOR_DECLAREP(Array, LinearDataStructure)
	VISITOR_DECLAREP(Matrix, LinearDataStructure)

};

