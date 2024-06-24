
#include "Pointer.h"
#include "BackLLVM.h"
#include "HeaderGlobals.h"
#include "UserType.h"

Pointer::Pointer(const char *name, DataType type, Node *address, location_t loc): 
    Variable(name, loc), address(address) {
    dt = type;
    addChild(address);
}

Value *Pointer::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
	auto sym = findSymbol(name, true);
	if (sym != NULL && sym != this) {
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

    if (!buildTypes->isDefined(dt)) {
        yyerrorcpp(string_format("The type %s is undefined.",
            buildTypes->name(dt)), this);
        return NULL;
    }

    Type *targetPointerType = buildTypes->llvmType(dt)->getPointerTo();

    // In favor of faster and smaller code size, we return the pointer
    // as a ConstantExpr. This limits pointer arithmetic.
    Constant *addr_num = dyn_cast<Constant>(addr);
    assert(addr_num && "FIXME: global pointer defined without constant address.");
    alloc = ConstantExpr::getIntToPtr(addr_num, targetPointerType);
    return alloc;
}

unsigned Pointer::getFieldStartBit(Node *field) {
    Node *dtsymbol = findSymbol(buildTypes->name(getDataType()));
    UserType *ut = dynamic_cast<UserType*>(dtsymbol);
    assert(ut && "Can't get field start bit from a non-complex type.");
    return ut->getFieldStartBit(field);
}
