
#include <iostream>
#include <map>

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/SubtargetFeature.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IR/AutoUpgrade.h>

#include "BackLLVM.h"

using namespace llvm;

// Program main module
Module* mainmodule;
BasicBlock* global_alloc;
LLVMContext global_context;
std::unique_ptr<IRBuilder<>> Builder;
std::unique_ptr<DIBuilder> DBuilder;
struct DebugInfo RobDbgInfo;
std::unique_ptr<BuildTypes> buildTypes;

unsigned int codeAddrSpace = 1;
unsigned int dataAddrSpace = 0;


// Injections
map<string, pair<string, BindScope>> injections;

enum SupportedTargets currentTargetId;
extern char *build_outputfilename;

TargetInfo supportedTargets[__last_target] = {
	{rb_native, "", "", "", "", tint64}, // default target
	{rb_avr,    "avr328p", "avr", "atmega328p", "+avr5", tint16},
	{rb_arm,    "stm32f1", "thumbv7m-none-eabi", "cortex-m3", "", tint32},
	{rb_xtensa, "esp32",   "xtensa",  "", "", tint32},
};

int print_llvm_ir(char opt_level) {
	
	const TargetInfo& ai = currentTarget();
	if (ai.backend == rb_native) {
		// Native target init
		InitializeNativeTarget();
		InitializeNativeTargetAsmParser();
		InitializeNativeTargetAsmPrinter();
	} else if (ai.backend == rb_avr) {
		// AVR target init
		LLVMInitializeAVRTargetInfo();
		LLVMInitializeAVRTarget();
		LLVMInitializeAVRTargetMC();
		LLVMInitializeAVRAsmParser();
		LLVMInitializeAVRAsmPrinter();
	} else if (ai.backend == rb_arm) {
		// ARM target init
		LLVMInitializeARMTargetInfo();
		LLVMInitializeARMTarget();
		LLVMInitializeARMTargetMC();
		LLVMInitializeARMAsmParser();
		LLVMInitializeARMAsmPrinter();
	} else {
		cerr << "No backend set for target " << ai.triple << ".\n";
		return 1;
	}

	std::string defaultt = sys::getDefaultTargetTriple();
	supportedTargets[0].triple = defaultt.c_str();
    SubtargetFeatures Features;
    StringMap<bool> HostFeatures;
    if (sys::getHostCPUFeatures(HostFeatures)) {
        for (auto &F : HostFeatures) {
            Features.AddFeature(F.first(), F.second);
		}
	}
	static string nativeFeatures = Features.getString();
    supportedTargets[0].features = nativeFeatures.c_str();

	std::string Error;
	auto Target = TargetRegistry::lookupTarget(ai.triple, Error);
	if (!Target) {
		errs() << Error;
		exit(1);
	}	

	TargetOptions opt;
	opt.FunctionSections = true;
	opt.DataSections = true;

	auto reloc = Reloc::PIC_;
	if (ai.backend == rb_arm)
		reloc = Reloc::Static;

	CodeGenOptLevel cgoptl = CodeGenOptLevel::None;
	switch (opt_level) {
		case '1': cgoptl = CodeGenOptLevel::Less; break;
		case '2': cgoptl = CodeGenOptLevel::Default; break;
		case '3':
		case 's':
		case 'z':
			cgoptl = CodeGenOptLevel::Aggressive;
			break;
	}

	auto targetMachine = Target->createTargetMachine(ai.triple, 
		ai.cpu, ai.features, opt, reloc, CodeModel::Small, cgoptl);

	mainmodule->setDataLayout(targetMachine->createDataLayout());
	mainmodule->setTargetTriple(ai.triple);
	mainmodule->setFramePointer(FramePointerKind::All);

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

	bool debugopt = false;
	OptimizationLevel ol;
	switch (opt_level) {
		case '0': ol = OptimizationLevel::O0; break;
		case '1': ol = OptimizationLevel::O1; break;
		case '2': ol = OptimizationLevel::O2; break;
		case '3': ol = OptimizationLevel::O3; break;
		case 's': ol = OptimizationLevel::Os; break;
		case 'd': debugopt = true; break;
		case 'z':
		default : ol = OptimizationLevel::Oz; break;
	}

	bool llvmir_errors = false;
	for(auto &f : mainmodule->getFunctionList()) {
		if (verifyFunction(f, &llvm::errs())) {
			cerr << endl << "Error(s) detected while verifying function " << f.getName().str() << endl;
			llvmir_errors = true;
		}
	}

	bool broken_debug = false;
	if (verifyModule(*mainmodule, &llvm::errs(), &broken_debug)) {
		cerr << endl << "Error(s) detected while verifying the global module." << endl;
		llvmir_errors = true;
	}

	if (broken_debug)
		cerr << "Errors in debug information were detected while verifying the global module." << endl;

	// This is used to see the llvm IR prior to any analysis.
	// Sometimes when adding new features, we want to see the IR even
	// it being invalid.
	if (debugopt) {
		mainmodule->print(outs(), nullptr);
		return 0;
	}

	if (llvmir_errors)
		return 1;

	UpgradeDebugInfo(*mainmodule);

	ModulePassManager modulePassManager;
	if (ol == OptimizationLevel::O0)
		modulePassManager = passBuilder.buildO0DefaultPipeline(ol);
	else
		//modulePassManager = passBuilder.buildPerModuleDefaultPipeline(ol);
		modulePassManager = passBuilder.buildThinLTODefaultPipeline(ol, nullptr);

	modulePassManager.run(*mainmodule, moduleAnalysisManager);

	if (build_outputfilename) {
		std::error_code ec;
		raw_fd_ostream dest(build_outputfilename, ec);
		if (ec) {
			printf("Error writing to %s.\n", build_outputfilename);
			exit(1);
		}
		legacy::PassManager pass_codegen;
		targetMachine->addPassesToEmitFile(pass_codegen, dest, nullptr, CodeGenFileType::ObjectFile);
		//targetMachine->addPassesToEmitFile(pass_codegen, dest, nullptr, CodeGenFileType::AssemblyFile);
		pass_codegen.run(*mainmodule);
		dest.close();
	} else {
		// print IR to stdout
		mainmodule->print(outs(), nullptr);
	}

	return 0;
}

const TargetInfo& currentTarget() {
	return supportedTargets[currentTargetId];
}

void setTarget(const char *targetarch) {
	currentTargetId = st_native; //native
	for(int t = st_native; t < __last_target; t++) {
		if (strcmp(targetarch, supportedTargets[t].name) == 0) {
			currentTargetId = static_cast<enum SupportedTargets>(t);
			break;
		}
	}

	// must set cpu before function generation
	if (currentTargetId == st_native) {
		static string defaultcpu = sys::getHostCPUName().str();
		supportedTargets[0].cpu = defaultcpu.c_str();
	}
}
