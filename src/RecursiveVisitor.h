#ifndef __RECURSIVE_VISITOR_H__
#define __RECURSIVE_VISITOR_H__
#include "Node.h"

class RecursiveVisitor: public Visitor {
public:
	void visit(Node const& n) override;
};

#endif



