
#include "CompoundStore.h"
#include "BinaryOp.h"
#include "semantic/PropagateTypes.h"

Value* CompoundStore::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    
    leftv->value->setToStore(true);
    Value *storeTo = leftv->value->generateNewBlock(func, &block, allocblock);

    bool isVolatile = false;
    LoadValue loadLeft(storeTo, leftv->value->getDataType(), isVolatile, this->getLoc());
    BinaryOp bp(&loadLeft, op, expr); 
    PropagateTypes pt;
    pt.visit(bp);

    Value *nvalue = bp.generateNewBlock(func, &block, allocblock);

    const DataLayout &DL = mainmodule->getDataLayout();
    Align align = DL.getABITypeAlign(nvalue->getType());
    return Builder->CreateAlignedStore(nvalue, storeTo, align, isVolatile);

}
