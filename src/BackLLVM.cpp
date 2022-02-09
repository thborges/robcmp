#include <map>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/InlineAsm.h>

#include <llvm/Passes/PassBuilder.h>
#include "llvm/IR/LegacyPassManager.h"

#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

// Program main module
Module *mainmodule;
BasicBlock *mainblock;
BasicBlock *global_alloc;
LLVMContext global_context;
static IRBuilder<> builder(global_context);

// symbol table
std::map<BasicBlock*, std::map<std::string, Value*>> tabelasym;

// arduino functions
Function *analogWrite;
Function *analogRead;
Function *delay;
Function *delayMicroseconds;
Function *init;
Function *print;
Function *i16div;

typedef struct {
	const char *name;
	const char *triple;
	const char *cpu;
	const char *features;
} TargetInfo;

TargetInfo supportedTargets[] = {
	{"", "", "", ""}, // default target
	{"avr328p", "avr-atmel-none", "atmega328p", "+avr5"},
};

void print_llvm_ir(const char *target, char opt_level) {
	
	InitializeAllTargetInfos();
	InitializeAllTargets();
	InitializeAllTargetMCs();
	InitializeAllAsmParsers();
	InitializeAllAsmPrinters();

	std::string defaultt = sys::getDefaultTargetTriple();
	supportedTargets[0].triple = defaultt.c_str();
	TargetInfo ai = supportedTargets[0];
	for(int t = 0; t < (sizeof(supportedTargets)/sizeof(TargetInfo)); t++) {
		if (strcmp(target, supportedTargets[t].name) == 0) {
			ai = supportedTargets[t];
			break;
		}
	}

	std::string Error;
	auto Target = TargetRegistry::lookupTarget(ai.triple, Error);
	if (!Target) {
		errs() << Error;
		exit(1);
	}	

	TargetOptions opt;
	auto RM = Optional<Reloc::Model>();
	auto targetMachine = Target->createTargetMachine(ai.triple, ai.cpu, ai.features, opt, RM);

	mainmodule->setDataLayout(targetMachine->createDataLayout());
	mainmodule->setTargetTriple(ai.triple);

	PassBuilder passBuilder(targetMachine);
	auto loopAnalysisManager = LoopAnalysisManager{};
	auto functionAnalysisManager = FunctionAnalysisManager{};
	auto cGSCCAnalysisManager = CGSCCAnalysisManager{};
	auto moduleAnalysisManager = ModuleAnalysisManager{};

	passBuilder.registerModuleAnalyses(moduleAnalysisManager);
	passBuilder.registerCGSCCAnalyses(cGSCCAnalysisManager);
	passBuilder.registerFunctionAnalyses(functionAnalysisManager);
	passBuilder.registerLoopAnalyses(loopAnalysisManager);
	passBuilder.crossRegisterProxies(
	    loopAnalysisManager, functionAnalysisManager, cGSCCAnalysisManager, moduleAnalysisManager);

	PassBuilder::OptimizationLevel ol;
	switch (opt_level) {
		//case '0': ol = PassBuilder::OptimizationLevel::O0; break;
		case '1': ol = PassBuilder::OptimizationLevel::O1; break;
		case '2': ol = PassBuilder::OptimizationLevel::O2; break;
		case '3': ol = PassBuilder::OptimizationLevel::O3; break;
		case 's': ol = PassBuilder::OptimizationLevel::Os; break;
		case 'z':
		default : ol = PassBuilder::OptimizationLevel::Oz; break;
	}

	if (opt_level != '0') {
		ModulePassManager modulePassManager =
	    	passBuilder.buildPerModuleDefaultPipeline(ol);
		modulePassManager.run(*mainmodule, moduleAnalysisManager);
	}

	//#define ENABLE_STDOUT
	#ifdef ENABLE_STDOUT
	std::string outfilename = filename;
	outfilename += ".o";
	std::error_code ec;
	raw_fd_ostream dest(outfilename, ec);
	if (ec) {
		printf("Error writing to %s.\n", outfilename.c_str());
		exit(1);
	}
	legacy::PassManager pass_codegen;
	targetMachine->addPassesToEmitFile(pass_codegen, dest, nullptr, TargetMachine::CGFT_ObjectFile);
	pass_codegen.run(*mainmodule);
	dest.flush();
	#endif

	// print IR to stdout
	mainmodule->print(outs(), nullptr);
}

