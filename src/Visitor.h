
#pragma once

#include "Node.h"

class BinaryOp;
class CmpOp;
class Delay;
class Float;
class FunctionCall;
class ConstructorCall;
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
class UpdateArray;
class While;
class Loop;
class UserType;
class Variable;
class NamedConst;
class MemCopy;
class Enum;
class BitCast;

#define VISITOR_DECLAREP(T, P) \
	virtual Node *visit(T& n) { return visit((P&)n); } \
	virtual void after(T&) {} \
	virtual bool before(T&) { return false; } \
	virtual Node *needs_replace(T&) { return NULL; }

#define VISITOR_DECLARE(T) \
	virtual Node *visit(T& n) { return visit((Node&)n); } \
	virtual void after(T&) {} \
	virtual bool before(T&) { return false; }

class Visitor {
public:
	virtual Node *visit(Node&) { return NULL; }
	virtual void after(Node&) {}
	virtual bool before(Node&) { return false; }

	VISITOR_DECLARE(NamedNode)
	VISITOR_DECLARE(BinaryOp)
	VISITOR_DECLARE(CmpOp)
	VISITOR_DECLARE(Delay)
	VISITOR_DECLARE(Float)
	VISITOR_DECLARE(FunctionCall)
	VISITOR_DECLARE(ConstructorCall)
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
	VISITOR_DECLAREP(Array, Variable)
	VISITOR_DECLAREP(Matrix, Variable)
	VISITOR_DECLARE(MemCopy)
	VISITOR_DECLARE(Enum)
	VISITOR_DECLARE(UpdateArray)
	VISITOR_DECLARE(BitCast)

};

