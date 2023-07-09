
#ifndef __VISITOR_H__
#define __VISITOR_H__

#include "Node.h"

#define VISITOR_DECLARE(T) \
	virtual void visit(T const&) {}; \
	virtual void after(T const&) {}; \
	virtual bool before(T const&) { return false; }

class Visitor {
public:
	VISITOR_DECLARE(Node);
	VISITOR_DECLARE(BinaryOp);
	VISITOR_DECLARE(Capsule);
	VISITOR_DECLARE(CmpOp);
	VISITOR_DECLARE(Delay);
	VISITOR_DECLARE(Float);
	VISITOR_DECLARE(FunctionCall);
	VISITOR_DECLARE(FunctionDecl);
	VISITOR_DECLARE(Matrix);
	VISITOR_DECLARE(If);
	VISITOR_DECLARE(InPort);
	VISITOR_DECLARE(Int16);
	VISITOR_DECLARE(Int32);
	VISITOR_DECLARE(Int8);
	VISITOR_DECLARE(Load);
	VISITOR_DECLARE(LoadArray);
	VISITOR_DECLARE(OutPort);
	VISITOR_DECLARE(Print);
	VISITOR_DECLARE(Program);
	VISITOR_DECLARE(Return);
	VISITOR_DECLARE(Scalar);
	VISITOR_DECLARE(Stmts);
	VISITOR_DECLARE(String);
	VISITOR_DECLARE(Array);
	VISITOR_DECLARE(While);
};

#endif

