
#include <regex>
#include "InlineAssembly.h"
#include "FunctionImpl.h"

Value *InlineAssembly::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

    Function *llvmFunction = func->getLLVMFunction();

    // Build a map with all argument names and the corresponding llvm::Argument*
    // TODO: Include local symbols in the map
    map<string, Argument*> argMap;
    for (auto &Arg : llvmFunction->args()) {
        argMap[Arg.getName().str()] = &Arg;
    }

    bool isFirst = true;
    std::string final_constraints;
    std::vector<llvm::Type*> ArgTypes;
    std::vector<llvm::Value*> Args;

    // constraints format supported:
    // "r(arg_name_1)"
    // "r(arg_name_1),r(arg_name_2),..."
    regex constraint_regex(R"(([0-9a-zA-Z]+)\(([^)]+)\))");
    smatch match;
    string::const_iterator searchStart(constraints.cbegin());

    while (std::regex_search(searchStart, constraints.cend(), match, constraint_regex)) {
        final_constraints += (isFirst ? "" : ",") + match[1].str();
        isFirst = false;
        std::string argName = match[2].str();
        auto it = argMap.find(argName);
        if (it != argMap.end()) {
            llvm::Argument* arg = it->second;
            ArgTypes.push_back(arg->getType());
            Args.push_back(arg);
        } else {
            yyerrorcpp(string_format("Parameter '%s' for assembly constraint not found.", 
                argName.c_str()), this);
        }
        searchStart = match.suffix().first;
    }

    // TODO: Add output constraint when there's r = asm(...) in the language
    // constraints = (isFirst ? "=r" : "=r," + constraints);
    // returnType = detect!
    // FunctionType *asmFuncType = FunctionType::get(returnType, ArgTypes, false);
    FunctionType *asmFuncType = FunctionType::get(Type::getVoidTy(global_context), ArgTypes, false);

    InlineAsm *asmcall = InlineAsm::get(asmFuncType, assembly, final_constraints, true, false, InlineAsm::AD_ATT);
    Error err = asmcall->verify(asmFuncType, constraints);
    if (err) {
        /* disabled due to false alerts
        std::string error_message;
        raw_string_ostream OS(error_message);
        OS << err;
        OS << " constraints: " << new_constraints;
        yywarncpp(error_message, this);*/
    }
    RobDbgInfo.emitLocation(this);
    Builder->SetInsertPoint(block);
    return Builder->CreateCall(asmFuncType, asmcall, Args);
}
