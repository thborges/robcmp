
#include "RecursiveVisitor.h"

void RecursiveVisitor::visit(Node& n) {
	if (before(n)) { return; }

	for (auto &c : n.children()) {
		c->accept(*this);
	}

	after(n);
}

