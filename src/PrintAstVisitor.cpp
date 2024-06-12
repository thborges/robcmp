
#define SCANNER_OR_VISITOR
#include "Header.h"
#include <cxxabi.h>
#include "Language_gen_y.hpp"
#include "Program.h"
#include "PrintAstVisitor.h"

template <typename T> char* get_typename(T& object)
{
    return abi::__cxa_demangle(typeid(object).name(), 0, 0, 0);
}

bool PrintAstVisitor::before(Node& n) {
	this->os << "N" << std::hex << (uint64_t)&n << 
		"[label=\"" << get_typename(n) << "\"];\n";
	return false;
}

void PrintAstVisitor::after(Node& n) {
}

void PrintAstVisitor::visit_children(Node& n) {
	for (Node *c : n.children()) {
		c->accept(*this);

		// print an edge between n and current child,
		// using object pointer as an identifier
		this->os << "N" << std::hex << (uint64_t)&n << "--" <<
					"N" << std::hex << (uint64_t)c << ";\n";
	}
}

Node* PrintAstVisitor::visit(Node& n) {
	if (before(n)) { return NULL; }
	visit_children(n);
	after(n);
	return NULL;
}

PrintAstVisitor::PrintAstVisitor(std::ostream& _os) : os(_os) {
}

Node* PrintAstVisitor::visit(Program& p) {
	if (before(p)) { return NULL; }
	visit_children(p);
	after(p);
	return NULL;
}

bool PrintAstVisitor::before(Program& p) {
	this->os << "graph {\nN"
		<< std::hex << (uint64_t)&p
		<< "[label=\"" << get_typename(p) 
		<< "\"];\n";
	return false;
}

void PrintAstVisitor::after(Program& p) {
	this->os << "}\n";
}

Node* PrintAstVisitor::visit(Int8& n) {
	this->os << "N" << std::hex << (uint64_t)&n << 
		"[label=\"" << get_typename(n) << "(" << std::dec << (int)n.getNumber() << ")\"];\n";
	return NULL;
}

Node* PrintAstVisitor::visit(Int16& n) {
	this->os << "N" << std::hex << (uint64_t)&n << 
		"[label=\"" << get_typename(n) << "(" << std::dec << n.getNumber() << ")\"];\n";
	return NULL;
}

Node* PrintAstVisitor::visit(Int32& n) {
	this->os << "N" << std::hex << (uint64_t)&n << 
		"[label=\"" << get_typename(n) << "(" << std::dec << n.getNumber() << ")\"];\n";
	return NULL;
}

const string PrintAstVisitor::getOperatorName(int op) {
	switch (op) {
		case EQ_OP: return "=";
		case NE_OP: return "!=";
		case LE_OP: return "<=";
		case GE_OP: return ">=";
		case LT_OP: return "<";
		case GT_OP: return ">";
		case TOK_AND : return "and";
		case TOK_OR  : return "or";
		default: return std::to_string(op);
	}
}

Node* PrintAstVisitor::visit(CmpOp& n) {
	this->os << "N" << std::hex << (uint64_t)&n 
			 << "[label=\"" << get_typename(n) << "(" << std::dec 
			 << getOperatorName(n.getOperator()) << ")\"];\n";
	visit_children(n);
	return NULL;
}

Node* PrintAstVisitor::visit(BinaryOp& n) {
	this->os << "N" << std::hex << (uint64_t)&n 
			 << "[label=\"" << get_typename(n) << "(" << std::dec 
			 << getOperatorName(n.getOperator()) << ")\"];\n";
	visit_children(n);
	return NULL;
}

Node* PrintAstVisitor::visit(Load& n) {
	this->os << "N" << std::hex << (uint64_t)&n 
			 << "[label=\"" << get_typename(n) << "(" << n.getName() << ")\"];\n";
	visit_children(n);
	return NULL;
}

Node* PrintAstVisitor::visit(Scalar& n) {
	this->os << "N" << std::hex << (uint64_t)&n 
			 << "[label=\"" << get_typename(n) << "(" << n.getName() << ")\"];\n";
	visit_children(n);
	return NULL;
}
