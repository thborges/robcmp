
#include "FlipOp.h"

FlipOp::FlipOp(Node *value) : value(value) {
    this->addChild(value);
};

Value *FlipOp::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    // generate code to produce the value to flip
	Value *exprv = value->generate(func, block, allocblock);
    if (exprv == NULL)
        return NULL;
    if (Constant *c = dyn_cast<Constant>(exprv))
        return ConstantExpr::getNot(c);
    else
        return BinaryOperator::Create(Instruction::Xor, exprv, 
            Constant::getAllOnesValue(exprv->getType()), "neg", block);
}

bool FlipOp::isConstExpr() {
	return value->isConstExpr();
}
