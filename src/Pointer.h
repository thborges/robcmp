#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "Header.h"

class Pointer: public Node {
private:
	LanguageDataType type;
    Node *address;
	string name;
	bool isVolatile;
public:
	Pointer(const char *name, LanguageDataType type, Node *address, bool isVolatile = false): 
		name(name), type(type), address(address), isVolatile(isVolatile) {}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor &v) override;
};

#endif
