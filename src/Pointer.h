#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "Header.h"

class Pointer: public Node {
private:
	BasicDataType type;
    Node *address;
	string name;
	bool isVolatile;
	Structure *structure;
public:
	Pointer(const char *name, BasicDataType type, Node *address, bool isVolatile = false): 
		name(name), type(type), address(address), isVolatile(isVolatile) {}
	Pointer(const char *name, BasicDataType type, Node *address, Structure *structure, 
		bool isVolatile = false): 
		name(name), type(type), address(address), structure(structure), isVolatile(isVolatile) {
		if (structure->nextBit > buildTypes->bitWidth(type)) {
			const char *emsg = "The sum of field sizes for %s (%d) is larger than its type size (%d).";
			yyerrorcpp(string_format(emsg, name, structure->nextBit, buildTypes->bitWidth(type)), this);
		}
	}
	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) override;
	virtual void accept(Visitor &v) override;
};

#endif
