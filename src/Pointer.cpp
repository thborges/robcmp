
#include "Pointer.h"

Pointer::Pointer(const char *name, DataType type, Node *address): 
    Variable(name), address(address) {
    dt = type;
    addChild(address);
}

Pointer::Pointer(const char *name, DataType type, Node *address, Structure *structure):
    Pointer(name, type, address) {
    if (structure->nextBit > buildTypes->bitWidth(type)) {
        const char *emsg = "The sum of field sizes for %s (%d) is larger than its type size (%d).";
        yyerrorcpp(string_format(emsg, name, structure->nextBit, buildTypes->bitWidth(type)), this);
    }
}

Value *Pointer::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock)
{
	auto sym = findSymbol(name, true);
	if (sym != NULL && sym != this) {
		yyerrorcpp("Register/pointer " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", sym);
		return NULL;
	}

    // valid register types
    /*if (!(dt == tint8 || dt == tint16 || dt == tint32 || dt == tint64)) {
        yyerrorcpp("Register " + name + " must be of int8, int16, int32 or int64 type.", this);
        return NULL;
    }*/

    // generate code to produce the address
    Value *addr = address->generate(func, block, allocblock);
    if (addr == NULL) {
        yyerrorcpp("Unable to compute the address for '" + name + "' register.", this);
        return NULL;
    }

    Type *targetPointerType = buildTypes->llvmType(dt)->getPointerTo();
    /*if (Constant *addrc = dyn_cast<Constant>(addr)) {
        alloc = ConstantExpr::getIntToPtr(addrc, targetPointerType);
    } else*/
    auto sp = RobDbgInfo.currScope();
    auto funit = RobDbgInfo.currFile();

    if (allocblock == global_alloc) {
        /*Constant *addr_num = dyn_cast<Constant>(addr);
        assert(addr_num && "FIXME: global pointer defined without constant address.");
        Constant *addr = ConstantExpr::getIntToPtr(addr_num, targetPointerType);
        GlobalVariable *gv = new GlobalVariable(*mainmodule, buildTypes->llvmType(dt),
           false, GlobalValue::CommonLinkage, addr, name);
        //gv->setUnnamedAddr(GlobalValue::UnnamedAddr::Local);
        //gv->setDSOLocal(true);
        alloc = gv;

        if (debug_info) {
            auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
                funit, getLineNo(), buildTypes->diType(dt), false);
            gv->addDebugInfo(d);
        }*/
        Constant *addr_num = dyn_cast<Constant>(addr);
        assert(addr_num && "FIXME: global pointer defined without constant address.");
        alloc = ConstantExpr::getIntToPtr(addr_num, targetPointerType);
    }
    else {
        alloc = new IntToPtrInst(addr, targetPointerType, name, allocblock);
    }

    return alloc;
}
