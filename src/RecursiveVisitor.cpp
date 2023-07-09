
#include "Header.h"

void RecursiveVisitor::visit(Node const& n) {
	if (before(n)) { return; }

	for (auto &c : n.children()) {
		c->accept(*this);
	}

	after(n);
}

