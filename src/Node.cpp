
#include "Node.h"
#include "Int8.h"
#include "Int16.h"
#include "Int32.h"
#include "Int64.h"
#include "Visitor.h"

Node::~Node() {}

Node::Node(vector<Node*> &&children, bool constructor) : node_children(children) {
	// scalars alread has their scope set in the type
	if (!constructor)
		setChildrenScope(this);
}

Node::Node(vector<Node*> &&children) : node_children(children) {
	setChildrenScope(this);
}

std::vector<Node *> const& Node::children() const {
	return node_children; 
}

void Node::accept(Visitor& v) {
	v.visit(*this);
}

Node* Node::findMember(const string& name) {
	// look for pseudo fields (array, matrix, register)
	Node *m = findSymbol(name, false);

	// force getting dataType in case it was not queried yet
	DataType this_dt = getDataType();

	if (!m && this_dt != BuildTypes::undefinedType) {
		// look for fields in the base type
		const char *ut_name = buildTypes->name(this_dt);
		Node *ut = findSymbol(ut_name);
		m = ut->findSymbol(name, false);
	}
	return m;
}

Node* Node::findSymbol(const string& name, bool recursive) {
	Node *current_scope = this;
	do {
		auto it = current_scope->symbols.find(name);
		if (it != current_scope->symbols.end()) {
			return it->second;
		} else if (recursive)
			current_scope = current_scope->scope;
	} while (current_scope && recursive);
	
	return NULL;
}

void Node::addChild(Node *n) {
	node_children.push_back(n);
}

void Node::addSymbol(NamedNode *nm) {
    // if the variable is already defined in a parent scope,
    // don't add it to symbols table in inner scopes.
    if (!findSymbol(nm->getName(), true)) {
		symbols[nm->getName()] = nm;
    }
}

map<string, NamedNode*> const& Node::getSymbols() {
	return symbols;
}

void Node::setScope(Node *s) {
	if (scope != NULL)
		assert(scope == NULL && "node already has a scope");
	scope = s;
/*	if (hasName())
		s->symbols[getName()] = dynamic_cast<NamedNode*>(this);
	for(auto& n : node_children) {
		if (!n->scope)
			n->setScope(s);
	}*/
}

void Node::setChildrenScope(Node *s) {
	for(auto& n : node_children) {
		//n->setScope(s);
	}
}

Value* Node::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return NULL;
}

Value* Node::generateChildren(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	for(Node *n: getChildren()) {
		Value *b = n->generate(func, block, allocblock);
		if (b && b->getValueID() == Value::BasicBlockVal) 
			block = (BasicBlock*)b;
	}
	return block;
}

extern Node* getNodeForIntConst(int64_t i) {
	if (i >= SCHAR_MIN && i <= SCHAR_MAX)
		return new Int8(i);
	else if (i >= SHRT_MIN && i <= SHRT_MAX)
		return new Int16(i);
	else if (i >= INT_MIN && i <= INT_MAX)
		return new Int32(i);
	else
		return new Int64(i);
}
