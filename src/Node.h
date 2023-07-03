#ifndef NODE_H
#define NODE_H

class Visitor;

class Node : public SourceLocation {
protected:
	std::vector<Node *> node_children;
public:
	virtual ~Node();

	virtual bool isFunctionDecl();
	
	virtual Value *constGenerate() {
		return generate(NULL, NULL, NULL);
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) = 0;

	virtual std::vector<Node *> const& children() const;
	virtual void accept(Visitor &);

};

#endif
