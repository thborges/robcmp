
#include "Header.h"
#include <cxxabi.h>

template <typename T> char* get_typename(T& object)
{
    return abi::__cxa_demangle(typeid(object).name(), 0, 0, 0);
}

PrintAstVisitorNode::PrintAstVisitorNode(std::ostream& _os) : os(_os) {
}

PrintAstVisitorNode::~PrintAstVisitorNode() {
}

bool PrintAstVisitorNode::before(Node const& n) {
	this->os << "N" << std::hex << (long int)&n << 
		"[label=\"" << get_typename(n) << "\"];\n";
	return false;
}

void PrintAstVisitorNode::visit_children(Node const& n) {
	for (Node *c : n.children()) {
		c->accept(*this);

		// print an edge between n and current child,
		// using object pointer as an identifier
		this->os << "N" << std::hex << (long int)&n << "--" <<
					"N" << std::hex << (long int)c << ";\n";
	}
}

void PrintAstVisitorNode::visit(Node const& n) {
	if (before(n)) { return; }
	visit_children(n);
	after(n);
}

PrintAstVisitor::PrintAstVisitor(std::ostream& _os) : PrintAstVisitorNode(_os) {
}

void PrintAstVisitor::visit(Program const& p) {
	if (before(p)) { return; }
	visit_children(p);
	after(p);
}

bool PrintAstVisitor::before(Program const& p) {
	this->os << "graph {\nN"
		<< std::hex << (long int)&p
		<< "[label=\"" << get_typename(p) 
		<< "\"];\n";
	return false;
}

void PrintAstVisitor::after(Program const& p) {
	this->os << "}\n";
}

void PrintAstVisitor::visit(Int8 const& n) {
	this->os << "N" << std::hex << (long int)&n << 
		"[label=\"" << get_typename(n) << "(" << std::dec << (int)n.getNumber() << ")\"];\n";
}

void PrintAstVisitor::visit(Int16 const& n) {
	this->os << "N" << std::hex << (long int)&n << 
		"[label=\"" << get_typename(n) << "(" << std::dec << n.getNumber() << ")\"];\n";
}

void PrintAstVisitor::visit(Int32 const& n) {
	this->os << "N" << std::hex << (long int)&n << 
		"[label=\"" << get_typename(n) << "(" << std::dec << n.getNumber() << ")\"];\n";
}

void PrintAstVisitor::visit(While const& n) {
	PrintAstVisitorNode::visit(n);
}

const string PrintAstVisitor::getOperatorName(int op) {
	switch (op) {
		case EQ_OP: return "=";
		case NE_OP: return "!=";
		case LE_OP: return "<=";
		case GE_OP: return ">=";
		case LT_OP: return "<";
		case GT_OP: return ">";
		case '+' : 	return "+";
		case '-' :  return "-";
		case '*' :  return "*";
		case '/' :  return "/";
		case '%' :  return "%";
		case TOK_AND : return "and";
		case TOK_OR  : return "or";
		default: return std::to_string(op);
	}
}

void PrintAstVisitor::visit(CmpOp const& n) {
	this->os << "N" << std::hex << (long int)&n 
			 << "[label=\"" << get_typename(n) << "(" << std::dec 
			 << getOperatorName(n.getOperator()) << ")\"];\n";
	visit_children(n);
}

void PrintAstVisitor::visit(BinaryOp const& n) {
	this->os << "N" << std::hex << (long int)&n 
			 << "[label=\"" << get_typename(n) << "(" << std::dec 
			 << getOperatorName(n.getOperator()) << ")\"];\n";
	visit_children(n);
}

void PrintAstVisitor::visit(Load const& n) {
	this->os << "N" << std::hex << (long int)&n 
			 << "[label=\"" << get_typename(n) << "(" << n.getIdent() << ")\"];\n";
	visit_children(n);
}

void PrintAstVisitor::visit(Scalar const& n) {
	this->os << "N" << std::hex << (long int)&n 
			 << "[label=\"" << get_typename(n) << "(" << n.getIdent() << ")\"];\n";
	visit_children(n);
}

void PrintAstVisitor::visit(Delay const& n) {
	PrintAstVisitorNode::visit(n);
}

void PrintAstVisitor::visit(If const& n) {
	PrintAstVisitorNode::visit(n);
}


