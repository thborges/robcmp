#include "Header.h"

Value *InlineAssembly::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
    Type *voidty = buildTypes->llvmType(tvoid);
	std::vector<Type*> arg_types;
	FunctionType *ftype = FunctionType::get(voidty, ArrayRef<Type*>(arg_types), false);
    InlineAsm *asmcall = InlineAsm::get(ftype, assembly, "", false, false, InlineAsm::AD_ATT);
    Error err = asmcall->verify(ftype, "");
    if (err) {
        std::string error_message;
        raw_string_ostream OS(error_message);
        OS << err;
        yyerrorcpp(error_message, this);
    }
    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);
    return Builder->CreateCall(ftype, asmcall, std::nullopt);
}
