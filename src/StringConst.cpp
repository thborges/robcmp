
#include "StringConst.h"
#include "BackLLVM.h"
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

    // const a = "abcdef" or a call to func("abc")
    if (!leftValue || leftValue->hasQualifier(qconst)) {
        Constant *zero = ConstantInt::get(Type::getInt32Ty(global_context), 0);
        Constant *indices[] = {zero, zero};
        value = ConstantExpr::getInBoundsGetElementPtr(gv->getValueType(), gv, indices);
    } else {
        // a = "abcdef", alloc array and copy string const to it
	    Type* I = buildTypes->llvmType(tchar);
        auto arrayType = ArrayType::get(I, str.size());

        // alloc array
        Builder->SetInsertPoint(allocblock);
        auto alloc = Builder->CreateAlloca(arrayType, dataAddrSpace, 0, leftValue->getName());
        if (debug_info) {
            RobDbgInfo.emitLocation(this);
            RobDbgInfo.declareVar(leftValue, alloc, allocblock);
        }
        leftValue->setAlloca(alloc);

        // copy string to the new array
		Builder->SetInsertPoint(block);
        Builder->CreateMemCpy(alloc, Align(1), gv, Align(1), str.size());
        value = alloc;
        
    }

    return value;
}
