
#pragma once

#include "SourceLocation.h"
#include "BuildTypes.h"

class Visitor;
class NamedNode;
class UserType;
class FunctionImpl;

class Node : public SourceLocation {
protected:
	map<string, NamedNode*> symbols;
	vector<Node*> node_children;
	DataType dt = BuildTypes::undefinedType;
	set<DataQualifier> qualifiers;
	Node *scope = nullptr;

public:
	Node() {}
	Node(vector<Node*> &&children);

	virtual ~Node();

	virtual bool isConstExpr() {
		return false;
	}
	
	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);
	
	virtual Value *generateChildren(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock);

	virtual std::vector<Node *> const& children() const;
	
	virtual void accept(Visitor &);

	virtual bool hasName() {
		return false;
	}

	virtual string const getName() const {
		return "";
	}

	Node *getScope() {
		return scope;
	}

	virtual void setScope(Node *s);

	virtual Node* findSymbol(const string& name, bool recursive = true);
	
	virtual Node* findMember(const string& name);

	void addChild(Node *n);

	map<string, NamedNode*> const& getSymbols();

	virtual void addSymbol(NamedNode *nm);

	void setDataType(DataType dt) {
		this->dt = dt;
	}

	virtual DataType getDataType() {
		return dt;
	}

	void setQualifier(DataQualifier dq) {
		qualifiers.insert(dq);
	}

	bool hasQualifier(DataQualifier dq) const {
		return qualifiers.count(dq) == 1;
	}

	virtual Value* getLLVMValue(Node *stem) {
		return NULL;
	}

	virtual void setLeftValue(Value *lv, const string& name) {}

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

	void setName(const string& nname) {
		name = nname;
	}

	bool hasName() override {
		return true;
	}
};
