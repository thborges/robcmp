#ifndef NODE_H
#define NODE_H

class Visitor;

class Node {
protected:
	std::vector<Node *> node_children;
public:
	virtual bool isFunctionDecl();
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) = 0;
	virtual ~Node();

	virtual std::vector<Node *> const& children() const;
	virtual void accept(Visitor &);
};

#endif
