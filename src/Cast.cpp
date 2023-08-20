
#include "Cast.h"
#include "Coercion.h"

Value *Cast::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
    Value *exprv = expr->generate(func, block, allocblock);
    if (!exprv)
        return NULL;

    Type *destty = buildTypes->llvmType(dt);
    Value *ret = Coercion::Convert(exprv, destty, block, expr, true);

    if (ret == NULL) {
        yyerrorcpp(string_format("Can't cast from '%s' to '%s'.",
            buildTypes->name(expr->getDataType()),
            buildTypes->name(dt)), this);
        return NULL;
    }

    return ret;
}
