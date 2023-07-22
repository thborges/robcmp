
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
    Value *addr = address->generate(func, block, allocblock);
    if (addr == NULL) {
        yyerrorcpp("Unable to compute the address for '" + name + "' register.", this);
        return NULL;
    }

    Type *targetPointerType = buildTypes->llvmType(currentTarget.pointerType);
    Value *addrp = NULL;
    if (Constant *addrc = dyn_cast<Constant>(addr))
        addrp = ConstantExpr::getIntToPtr(addrc, targetPointerType);
    else
        addrp = new IntToPtrInst(addr, targetPointerType, name, allocblock);
        
    Type *ty = buildTypes->llvmType(type);
    DataQualifier vol = isVolatile ? qvolatile : qnone;
    
    RobSymbol *rs = new RobSymbol(addrp, vol);
    rs->structure = structure;
    rs->setLocation(this);
    rs->dt = type;
    tabelasym[allocblock][name] = rs;
    
    return addrp;
}

void Pointer::accept(Visitor &v) {
	v.visit(*this); 
}

