
#pragma once

#include "Node.h"
#include "Visitor.h"

class RecursiveVisitor: public Visitor {
public:
	Node* visit(Node& n) override;
};
