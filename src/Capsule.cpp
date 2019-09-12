
#include "Header.h"

Value *Capsule::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return node->generate(func, block, allocblock);
}

