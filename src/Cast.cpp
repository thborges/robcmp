
#include "Header.h"

BasicDataType Cast::getResultType(BasicBlock *block, BasicBlock *allocblock) { 
    return dt;
}

Value *Cast::generate(Function *func, BasicBlock *block, BasicBlock *allocblock)
{
    Value *exprv = expr->generate(func, block, allocblock);
    if (!exprv)
        return NULL;

    Type *destty = buildTypes->llvmType(dt);
    Value *ret = Coercion::Convert(exprv, destty, block, expr, true);

    if (ret == NULL) {
        yyerrorcpp("Can't cast from '" + getTypeName(exprv->getType()) + "' to '" + 
            buildTypes->name(dt), this);
        return NULL;
    }

    return ret;
}

void Cast::accept(Visitor &v) {
	v.visit(*this); 
}
