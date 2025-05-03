
#include "RecursiveVisitor.h"

Node* RecursiveVisitor::visit(Node& n) {
	if (before(n)) { return NULL; }

	for (auto &c : n.children()) {
		c->accept(*this);
	}

	after(n);
	return NULL;
}

