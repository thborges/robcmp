
#pragma once

class Visitor;
class NamedNode;
class UserType;

class Node : public SourceLocation {
protected:
	vector<Node*> node_children;
	map<string, Node*> symbols;
	Node *parent = nullptr;
	bool update_names = false;

	virtual void updateNamedNodes() {
		for(Node *n : node_children) {
			if (n->hasName())
				symbols[n->getName()] = n;
		}
	}

public:
	Node() {}
	Node(vector<Node *> &&children) : node_children(children) {
		updateNamedNodes();
		update_names = false;
		for(auto c : children)
			c->setParent(this);
	}

	virtual ~Node();

	virtual bool isFunctionDecl();

	virtual bool isConstExpr(BasicBlock *block, BasicBlock *allocblock) {
		return false;
	}
	
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) = 0;

	virtual std::vector<Node *> const& children() const;
	
	virtual void accept(Visitor &);

	virtual BasicDataType getResultType(BasicBlock *block, BasicBlock *allocblock) {
		/* this method should be overrided in descending classes 
		 * that define vars/consts
		 */
		return tvoid;
	}

	virtual bool hasName() {
		return false;
	}

	virtual string const getName() const {
		return "";
	}

	Node *getParent() {
		return parent;
	}

	virtual void setParent(Node *p) {
		parent = p;
	}

	virtual Node* findSymbol(const string& name, bool recursive = true) {
		auto it = symbols.find(name);
		if (it != symbols.end()) {
			return it->second;
		} else if (recursive && parent)
			return parent->findSymbol(name);
		else
			return nullptr;
	}

	friend class UserType;
	friend class Program;
};

class NamedNode: public Node {
protected:
	string name;

public:
	NamedNode(const string &name) : name(name) {}

	NamedNode(const string &name, vector<Node*> &&children) : 
		Node(std::move(children)), name(name) {}
	
	string const getName() const override {
		return name;
	}

	bool hasName() override {
		return true;
	}
};
