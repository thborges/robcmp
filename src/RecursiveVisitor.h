
#pragma once

#include "Node.h"
#include "Visitor.h"

class RecursiveVisitor: public Visitor {
public:
	void visit(Node& n) override;
};
