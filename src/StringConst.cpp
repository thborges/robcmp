
#include "StringConst.h"
#include "NamedConst.h"

StringConst::StringConst(const string& name, const string& str, location_t loc) :
    Array(name, loc), str(str) {  
    NamedConst *nc = new NamedConst("size", getNodeForUIntConst(str.size(), loc));
	addChild(nc);
	addSymbol(nc);
}

Value* StringConst::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
    Builder->SetInsertPoint(block);
    return Builder->CreateGlobalStringPtr(str, name);
}
