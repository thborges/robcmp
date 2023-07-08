#ifndef NODE_H
#define NODE_H

class Visitor;

class Node : public SourceLocation {
protected:
	std::vector<Node *> node_children;
public:
	virtual ~Node();

	virtual bool isFunctionDecl();
	virtual bool isConstExpr() {
		return false;
	}
	
	virtual Value *constGenerate() {
		if (isConstExpr())
			return generate(NULL, NULL, NULL);
		else
			return NULL;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) = 0;

	virtual std::vector<Node *> const& children() const;
	virtual void accept(Visitor &);

	virtual Type *getLLVMResultType(BasicBlock *block, BasicBlock *allocblock) {
		/* this method should be overrided in descending classes used
		 * to define other vars/consts
		 */
		return NULL;
	}
};

#endif
