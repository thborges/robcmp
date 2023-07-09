#include "Header.h"

bool Node::isFunctionDecl()
{
	return false;
}

Node::~Node() {}

std::vector<Node *> const& Node::children() const {
	return node_children; 
}

void Node::accept(Visitor& v) {
	v.visit(*this);
}

