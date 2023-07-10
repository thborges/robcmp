
#include "Header.h"

Malloc::Malloc(Node *e) : expr(e) {
	node_children.reserve(1);
	node_children.push_back(e);
}
	Value *Malloc::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		Value *exprv = expr->generate(func, block, allocblock);
		Type *leftvty = exprv->getType();
		Value *m_size = ConstantInt::get(Type::getInt8Ty(global_context), 0);
		return CallInst::CreateMalloc(block, Type::getInt32Ty(global_context), leftvty, m_size, m_size, func, "");
	}
