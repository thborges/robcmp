
#include "Capsule.h"

Value *Capsule::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return node->generate(func, block, allocblock);
}

