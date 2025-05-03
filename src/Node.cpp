
#include "Node.h"
#include "Int8.h"
#include "Int16.h"
#include "Int32.h"
#include "Int64.h"
#include "Visitor.h"

Node::~Node() {}

Node::Node(vector<Node*> &&children, location_t loc) : SourceLocation(loc), node_children(children) {
}

std::vector<Node *> const& Node::children() const {
	return node_children; 
}

Node* Node::accept(Visitor& v) {
	return v.visit(*this);
}

Node* Node::findMember(const string& name) {
	// look for pseudo fields (array, matrix, register)
	Node *m = findSymbol(name, false);
	if (!m) {
		// getDataType forces getting the dataType, case it was not queried yet
		DataType this_dt = getDataType();
		if (this_dt == BuildTypes::undefinedType)
			return m;

		// look for fields in the base type
		const char *ut_name = buildTypes->name(this_dt);
		Node *ut = findSymbol(ut_name);
		if (!ut)
			return NULL;
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

void Node::addChild(Node *n, bool prepend) {
	if (prepend)
		node_children.insert(node_children.begin(), n);
	else
		node_children.push_back(n);
}

void Node::removeChild(Node *n) {
	NamedNode *nn = dynamic_cast<NamedNode*>(n);
	if (nn)
		symbols.erase(nn->getName());
	auto it = find(node_children.begin(), node_children.end(), n);
	if (*it)
		node_children.erase(it);
}

void Node::addSymbol(NamedNode *nm) {
	addSymbol(nm->getName(), nm);
}

void Node::addSymbol(const string& label, NamedNode *nm) {
    // if the variable is already defined here or in a parent
	// scope, don't add it again.
    if (!findSymbol(label, true)) {
		symbols[label] = nm;
    }
}

map<string, NamedNode*> const& Node::getSymbols() {
	return symbols;
}

void Node::setScope(Node *s, bool replace) {
	if (scope != NULL && !replace)
		assert(scope == NULL && "node already has a scope");
	scope = s;
}

Value* Node::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return NULL;
}

Value* Node::generateChildren(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	for(Node *n: children()) {
		Value *b = n->generate(func, block, allocblock);
		if (b) {
			if (b->getValueID() == Value::BasicBlockVal) 
				block = (BasicBlock*)b;
			else if (Instruction* instr = dyn_cast<Instruction>(b)) {
				// A distinct block can return from boolean short-circuit evaluation
				if (instr->getParent() != allocblock)
					block = instr->getParent();
			}
		}
	}
	return block;
}

Type* Node::getLLVMType() {
	DataType aux = getDataType();
	Type *taux = buildTypes->llvmType(getDataType());
	if (buildTypes->isInterface(aux))
		return taux->getPointerTo();
	else
		return taux;
}

Node* getNodeForUIntConst(uint64_t i, location_t loc) {
	if (i <= UCHAR_MAX)
		return new UInt8(i, loc);
	else if (i <= USHRT_MAX)
		return new UInt16(i, loc);
	else if (i <= UINT_MAX)
		return new UInt32(i, loc);
	else
		return new UInt64(i, loc);
}

Node* getNodeForIntConst(int64_t i, location_t loc) {
	if (i >= SCHAR_MIN && i <= SCHAR_MAX)
		return new Int8(i, loc);
	else if (i >= SHRT_MIN && i <= SHRT_MAX)
		return new Int16(i, loc);
	else if (i >= INT_MIN && i <= INT_MAX)
		return new Int32(i, loc);
	else
		return new Int64(i, loc);
}
