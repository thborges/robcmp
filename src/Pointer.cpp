
#include "Pointer.h"

Value *Pointer::generate(Function *func, BasicBlock *block, BasicBlock *allocblock)
{
	auto sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Register/pointer " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", sym);
		return NULL;
	}

    // generate code to produce the address
    Value *addri = address->generate(func, block, allocblock);
    if (addri == NULL) {
        yyerrorcpp("Unable to compute the address for '" + name + "' register.", this);
        return NULL;
    }

    Value *addrp = NULL;
    if (Constant *addrc = dyn_cast<Constant>(addri))
        addrp = ConstantExpr::getIntToPtr(addrc, Type::getInt64PtrTy(global_context)); // FIXME: What is the method to get an opaque pointer type?
    else
        addrp = new IntToPtrInst(addri, Type::getInt64PtrTy(global_context), name, allocblock);
        
    Type *ty = robTollvmDataType[type];
    DataQualifier vol = isVolatile ? qvolatile : qnone;
    tabelasym[allocblock][name] = new RobSymbol(addrp, vol, ty);
    return addrp;
}

void Pointer::accept(Visitor &v) {
	v.visit(*this); 
}

