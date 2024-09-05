
#include "StringConst.h"
#include "NamedConst.h"

StringConst::StringConst(const string& name, const string& str, location_t loc) :
    Array(name, loc), str(str) {  
    NamedConst *nc = new NamedConst("size", getNodeForUIntConst(str.size(), loc));
	addChild(nc);
	addSymbol(nc);
}

Value* StringConst::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    Builder->SetInsertPoint(allocblock);

    if (value)
        return value;

    Constant *constant = ConstantDataArray::getString(global_context, str, false);
    auto *gv = new GlobalVariable(
        *mainmodule, constant->getType(), true, GlobalValue::PrivateLinkage,
        constant, name);
    gv->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    gv->setAlignment(Align(1));
    Constant *zero = ConstantInt::get(Type::getInt32Ty(global_context), 0);
    Constant *indices[] = {zero, zero};
    value = ConstantExpr::getInBoundsGetElementPtr(gv->getValueType(), gv, indices);
    return value;
}
