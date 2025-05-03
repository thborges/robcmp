#include "Program.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "SymbolizeTree.h"
#include "PropagateTypes.h"
#include "PrintAstVisitor.h"
#include "BackLLVM.h"
#include "UndefInit.h"
#include "Return.h"
#include "Load.h"
#include "BuildTypes.h"
#include "ConstructorCall.h"
#include <cstddef>

Program::Program() : Node({0,0,0,0}) {
	mainmodule = new Module(this->getFile(), global_context);
	Builder = make_unique<IRBuilder<>>(global_context);

	if (debug_info) {
		mainmodule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
		mainmodule->addModuleFlag(Module::Warning, "Dwarf Version", 4);
		DBuilder = make_unique<DIBuilder>(*mainmodule);
		RobDbgInfo.cunit = DBuilder->createCompileUnit(dwarf::DW_LANG_C11,
			DBuilder->createFile(this->getFile(), std::filesystem::current_path().string()),
			"Robcmp", false, "", 0);

		// global scope
		RobDbgInfo.push_file(RobDbgInfo.cunit->getFile());
		RobDbgInfo.push_scope(RobDbgInfo.cunit);
	}
	
	buildTypes = make_unique<BuildTypes>(currentTarget().pointerType, this);
	global_alloc = BasicBlock::Create(global_context, "global");

	dispatch = new Dispatch();
}

Program::~Program() {
	delete dispatch;
	delete mainmodule;
}

Value *Program::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return NULL;
}

void Program::generateInjectionSetup(SourceLocation *sl) {

	location_t loc = sl->getLoc();

	// a function to init global vars for singleton injections
	FunctionImpl *funcInitGlobals = new FunctionImpl((DataType)tvoid, "__injections_init", 
		new FunctionParams(), vector<Node *>(), loc, loc, false);
	funcInitGlobals->setScope(this);
	addSymbol(funcInitGlobals);

	/* create a function for each injection, named :get_injection_for_[to]:
	    function :get_injection_for_[to] {
	      static instance = type()
		  return instance;
		}
	*/
	vector<FunctionImpl*> finjects;
	for (auto &[key, itype] : injections) {
		Identifier to(key, loc);
		Identifier bind(itype->bind, loc);

		// injection validation
		auto subTypeName = regex_replace(bind.getFullName(), regex("\\."), ":"); //internal types use :
		Identifier bindSubtypes(subTypeName, loc);
		Node *injectType = bindSubtypes.getSymbol(this, false);
		if (!injectType) {
			yyerrorcpp(string_format("Injection symbol %s not found.", 
				bind.getFullName().c_str()), &itype->loc);
			continue;
		}

		DataType destinationTy = BuildTypes::undefinedType;
		string destinationTyName;
		UserType *bindUserTy = dynamic_cast<UserType*>(injectType);
		if (!bindUserTy) {
			yyerrorcpp(string_format("Bind symbol %s is not of a bindable type.",
				bind.getFullName().c_str()), &itype->loc);
			continue;
		} else {
			Node *nodeTo = to.getSymbol(this, false);
			if (!nodeTo) {
				yyerrorcpp(string_format("Injection destination %s not found.",
					to.getFullName().c_str()), &itype->loc);
				continue;			
			} else {
				destinationTy = nodeTo->getDataType();
				destinationTyName = buildTypes->name(destinationTy);
				if (!bindUserTy->implementsInterface(destinationTyName)) {
					yyerrorcpp(string_format("Bind symbol %s does not implements %s.",
						bind.getFullName().c_str(), destinationTyName.c_str()), bindUserTy);				
					continue;
				}
			}
		}

		// setup dispatcher to resolv from destinationTy to bindUserTy
		program->getDispatcher()->addDataTypeImplementation(destinationTy,
			bindUserTy->getDataType());

		// generate injection stuff

		const string functionName = "__get_injection_for_" + to.getFullName();
		FunctionImpl *finject = new FunctionImpl(destinationTy, functionName, 
			new FunctionParams(), vector<Node *>(), loc, loc, false);
		finject->setReturnIsPointer(true);
		finject->setScope(this);
		finject->setAttributes(new FunctionAttributes(fa_inline));
		
		if (itype->scope == bs_singleton) {
			string globalVarName;
			if (bind.isComplex()) {
				globalVarName = "__var_injection_for_" + bind.getFullName();
			} else {
				globalVarName = "__var_injection_for_" + bind.getFullName();
				Node *var = findSymbol(globalVarName);
				if (!var) {
					// alloc the global var
					UndefInit *nc = new UndefInit(injectType->getDataType(), loc);
					Scalar *svar = new Scalar(globalVarName, nc);
					svar->setScope(this);
					addSymbol(svar);
					svar->generate(NULL, NULL, global_alloc);
					var = svar;

					ConstructorCall *cc = new ConstructorCall(bind.getFullName(), loc);
					Scalar *sc = new Scalar(globalVarName, cc);
					cc->setScope(funcInitGlobals);
					sc->setScope(funcInitGlobals);
					funcInitGlobals->addChild(sc);
				}
			}

			Load *load = new Load(Identifier(globalVarName, loc));
			Return *ret = new Return(load);
			ret->setScope(finject);
			load->setScope(finject);
			finject->addChild(ret);
			finjects.push_back(finject);

		} else { // bs_transient
			assert(false && "TODO: implement bs_transient scope.");
		}
	}

	for(auto *finject : finjects)
		finject->generate(NULL, NULL, global_alloc);

	funcInitGlobals->generate(NULL, NULL, global_alloc);
}

void Program::declareBuiltins() {

	// typeid function
	FunctionParams *typeid_params = new FunctionParams();
	typeid_params->append(new Variable("object", tobject, this->getLoc()));
	FunctionDecl *typeid_decl = new FunctionDecl(tint8u, "typeid", typeid_params, this->getLoc());
	typeid_decl->setLinkage(GlobalValue::LinkOnceODRLinkage);
	addChild(typeid_decl);
	addSymbol(typeid_decl);
}

void Program::generateBuiltins() {	
	// generate the typeid declaration
	Node *decl = findSymbol("typeid");
	Value *typeidValue = decl->generate(NULL, NULL, global_alloc);
	Function *typeidFunc = dyn_cast<Function>(typeidValue);

	// generate the typeid implementation
	BasicBlock *body = BasicBlock::Create(global_context, "", typeidFunc);
	Builder->SetInsertPoint(body);
	auto& Arg = *typeidFunc->args().begin();
	Arg.addAttr(Attribute::ReadOnly);
	auto *CmpVoid = Builder->CreateCmp(FCmpInst::ICMP_EQ, &Arg, ConstantPointerNull::get(Arg.getType()->getPointerTo()));
	
	// if pointer is not set, return zero/void
	BasicBlock *returnVoid = BasicBlock::Create(global_context, "", typeidFunc);
	Builder->SetInsertPoint(returnVoid);
	Builder->CreateRet(ConstantInt::get(typeidFunc->getReturnType(), 0));

	// else, return the object typeid
	BasicBlock *returnTypeid = BasicBlock::Create(global_context, "", typeidFunc);
	Builder->SetInsertPoint(returnTypeid);
	Value *zero = ConstantInt::get(Type::getInt8Ty(global_context), 0);
	Value *indexList[2] = {zero, zero};
	Type *idType = Type::getInt8Ty(global_context);
	Value *idValue = Builder->CreateLoad(typeidFunc->getReturnType(), &Arg);
	Builder->CreateRet(idValue);

	Builder->SetInsertPoint(body);
	Builder->CreateCondBr(CmpVoid, returnVoid, returnTypeid);

}

extern bool parseIsCompleted;

void Program::doSemanticAnalysis() {
    parseIsCompleted = true;

	declareBuiltins();

	// instrumentation passes
	SymbolizeTree st;
	st.visit(*this);

	PropagateTypes pt;
	pt.visit(*this);

	buildTypes->generateDebugInfoForTypes();

	/*std::fstream fs;
	fs.open("ast", std::fstream::out);
	PrintAstVisitor(fs).visit(*this);
	fs.close();*/
}

void Program::generate() {

	Node *mainFunc = NULL;

	generateBuiltins();

	for(auto n: children()) {
		if (FunctionImpl *func = dynamic_cast<FunctionImpl*>(n)) {
			if (func->getName() == "main" || func->getName() == "__main") {
				// generate main function after all others
				mainFunc = n;
				continue;
			}
		}

		n->generate(NULL, NULL, global_alloc);
	}

	if (mainFunc && injections.size() > 0) {
		generateInjectionSetup(mainFunc);

		FunctionCall *fc = new FunctionCall("__injections_init", new ParamsCall(), mainFunc->getLoc());
		fc->setScope(mainFunc);
		mainFunc->addChild(fc, true);
	}

	FunctionType *global_init_type = FunctionType::get(Type::getVoidTy(global_context), ArrayRef<Type*>(), false);
	Function *global_init = NULL;
	if (mainFunc && global_alloc->size() > 0) {
		// create a function named :global_init to init global vars by calling their constructors
		global_init = Function::Create(global_init_type, Function::ExternalLinkage, codeAddrSpace, 
			"__globals_init", mainmodule);
		global_init->addFnAttr(Attribute::AlwaysInline);
		global_init->setCallingConv(CallingConv::C);

		// clear debug information as we will move instructions to __globals_init
		vector<Instruction*> remove;
		for (auto &a : *global_alloc) {
			if (a.getOpcode() == Instruction::Call) { 
				CallInst *call = dyn_cast<CallInst>(&a);
				if (call->getCalledFunction()->isDeclaration()) {
					a.replaceAllUsesWith(UndefValue::get(call->getType()));
					remove.push_back(call);
					continue;
				}
			}
			a.setDebugLoc(DebugLoc());
		}
		for(auto *i : remove) {
			i->dropAllReferences();
			i->removeFromParent();
		}
		Builder->SetInsertPoint(global_alloc);
		Builder->CreateRetVoid();
		global_init->insert(global_init->end(), global_alloc);
	}

	if (mainFunc) {
		// add naked attribute to main to prevent backend
		// of emmiting prologue and epilogue, as it is the
		// first call in the stack
		/*if (currentTargetId != st_native)
			if (FunctionImpl *fi = dynamic_cast<FunctionImpl*>(mainFunc))
				fi->getAttributes()->addAttribute(fa_naked);*/

		mainFunc->generate(NULL, NULL, global_alloc);

		if (global_init) {
			Function *mainf = mainmodule->getFunction("main");
			BasicBlock *entryBlock = &mainf->getEntryBlock();
			Builder->SetInsertPoint(entryBlock->end()->getPrevNode()); // before br
			Builder->CreateCall(global_init_type, global_init);
		}
	}

	dispatch->generateDispatchFunctions(program);

	if (debug_info)
		DBuilder->finalize();
}
