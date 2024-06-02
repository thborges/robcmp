#include "Program.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "SymbolizeTree.h"
#include "BackLLVM.h"
#include "ZeroInit.h"
#include "Return.h"
#include "Load.h"
#include "BuildTypes.h"
#include <cstddef>

Program::Program() {
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
		RobDbgInfo.push_scope(RobDbgInfo.cunit->getFile(), RobDbgInfo.cunit);
	}
	
	buildTypes = make_unique<BuildTypes>(currentTarget().pointerType);
	global_alloc = BasicBlock::Create(global_context, "global");
}

void Program::declara_auxiliary_c_funcs() {
	std::vector<Type*> arg_types;
	FunctionType *ftype;

	#ifdef ENABLE_ARDUINO
	// analogRead
	arg_types.clear();
	arg_types.push_back(Type::getInt8Ty(global_context));
	ftype = FunctionType::get(Type::getInt16Ty(global_context),
		ArrayRef<Type*>(arg_types), false);
	analogRead = Function::Create(ftype, Function::ExternalLinkage, "analogRead", mainmodule);
	analogRead->setCallingConv(CallingConv::C);

	// analogWrite or digitalWrite
	arg_types.clear();
	arg_types.push_back(Type::getInt8Ty(global_context));
	arg_types.push_back(Type::getInt16Ty(global_context));
	ftype = FunctionType::get(Type::getVoidTy(global_context),
		ArrayRef<Type*>(arg_types), false);
	analogWrite = Function::Create(ftype, Function::ExternalLinkage, "analogWrite", mainmodule);

	// digitalWrite instead
	/*arg_types.clear();
	arg_types.push_back(Type::getInt8Ty(global_context));
	arg_types.push_back(Type::getInt8Ty(global_context));
	ftype = FunctionType::get(Type::getVoidTy(global_context),
		ArrayRef<Type*>(arg_types), false);
	analogWrite = Function::Create(ftype, Function::ExternalLinkage, "digitalWrite", mainmodule);
	*/

	analogWrite->setCallingConv(CallingConv::C);

	// delay 
	arg_types.clear();
	arg_types.push_back(Type::getInt32Ty(global_context));
	ftype = FunctionType::get(Type::getVoidTy(global_context),
		ArrayRef<Type*>(arg_types), false);
	delay = Function::Create(ftype, Function::ExternalLinkage, "delay", mainmodule);
	delay->setCallingConv(CallingConv::C);


	// delayMicroseconds
	arg_types.clear();
	arg_types.push_back(Type::getInt32Ty(global_context));
	ftype = FunctionType::get(Type::getVoidTy(global_context),
		ArrayRef<Type*>(arg_types), false);
	delayMicroseconds = Function::Create(ftype, Function::ExternalLinkage, "delayMicroseconds", mainmodule);
	delayMicroseconds->setCallingConv(CallingConv::C);
	
	// init
	ftype = FunctionType::get(Type::getVoidTy(global_context), false);
	init = Function::Create(ftype, Function::ExternalLinkage, "init", mainmodule);
	init->setCallingConv(CallingConv::C);
	#endif

	#ifdef ENABLE_PRINT
	// print
	arg_types.clear();
	arg_types.push_back(Type::getInt8Ty(global_context));
	arg_types.push_back(PointerType::get(IntegerType::get(global_context, 8), 0));
	ftype = FunctionType::get(Type::getVoidTy(global_context),
		ArrayRef<Type*>(arg_types), false);
	print = Function::Create(ftype, Function::ExternalLinkage, "print", mainmodule);
	print->setCallingConv(CallingConv::C);
	#endif

	/* Not necessary anymore. Stay as an example
	AttributeSet print_func_attrs;
	print_func_attrs = 
		print_func_attrs.addAttribute(global_context, AttributeSet::FunctionIndex, Attribute::NoUnwind)
							.addAttribute(global_context, AttributeSet::FunctionIndex, Attribute::StackProtect)
							.addAttribute(global_context, AttributeSet::FunctionIndex, Attribute::UWTable)
							.addAttribute(global_context, 1, Attribute::ZExt);
	print->setAttributes(print_func_attrs); */

	// i16divse)
	/*arg_types.clear();
	arg_types.push_back(Type::getInt16Ty(global_context));
	arg_types.push_back(Type::getInt16Ty(global_context));
	ftype = FunctionType::get(Type::getInt16Ty(global_context),
		ArrayRef<Type*>(arg_types), false);
	i16div = Function::Create(ftype, Function::ExternalLinkage, "i16div", mainmodule);
	i16div->setCallingConv(CallingConv::C);*/
}

Value *Program::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {
	return NULL;
}

void Program::generateInjectionSetup() {

	// a function to init global vars for singleton injections
	FunctionImpl *funcInitGlobals = new FunctionImpl((DataType)tvoid, ":injections_init", 
		new FunctionParams(), vector<Node *>(), *this->getLoct(), false);
	funcInitGlobals->setScope(this);
	addSymbol(funcInitGlobals);

	/* create a function for each injection, named :get_injection_for_[to]:
	    function :get_injection_for_[to] {
	      static instance = type()
		  return instance;
		}
	*/
	for (auto &[key, itype] : injections) {
		Identifier to(key);
		Identifier bind(itype.first);
		BindScope scope(itype.second);

		// injection validation
		Identifier bindSubtypes = regex_replace(bind.getFullName(), regex("\\."), ":"); //internal types use :
		Node *injectType = bindSubtypes.getSymbol(this);
		if (!injectType) {
			yyerrorcpp(string_format("Injection symbol %s not found.", 
				bind.getFullName().c_str()), this);
			continue;
		}

		DataType destinationTy = BuildTypes::undefinedType;
		string destinationTyName;
		UserType *bindUserTy = dynamic_cast<UserType*>(injectType);
		if (!bindUserTy) {
			yyerrorcpp(string_format("Bind symbol %s is not of a bindable type.",
				bind.getFullName().c_str()), this);
			continue;
		} else {
			Node *nodeTo = to.getSymbol(this);
			if (!nodeTo) {
				yyerrorcpp(string_format("Injection destination %s not found.",
					bind.getFullName().c_str()), this);
				continue;			
			} else {
				destinationTy = nodeTo->getDataType();
				destinationTyName = buildTypes->name(destinationTy);
				if (!bindUserTy->implementsInterface(destinationTyName)) {
					yyerrorcpp(string_format("Bind symbol %s does not implements %s.",
						bind.getFullName().c_str(), destinationTyName.c_str()), this);				
					continue;
				}
			}
		}

		// generate injection stuff

		const string functionName = ":get_injection_for_" + to.getFullName();
		FunctionImpl *finject = new FunctionImpl(destinationTy, functionName, 
			new FunctionParams(), vector<Node *>(), *this->getLoct(), false);
		finject->setReturnIsPointer(true);
		finject->setScope(this);
		
		if (scope == bs_singleton) {
			string globalVarName;
			if (bind.isComplex()) {
				globalVarName = ":var_injection_for_" + bind.getFullName();
			} else {
				globalVarName = ":var_injection_for_" + bind.getFullName();
				Node *var = findSymbol(globalVarName);
				if (!var) {
					// alloc the global var
					ZeroInit *nc = new ZeroInit(injectType->getDataType());
					Scalar *svar = new Scalar(globalVarName, nc);
					svar->setScope(this);
					addSymbol(svar);
					svar->generate(NULL, NULL, global_alloc);
					var = svar;

					FunctionCall *fc = new FunctionCall(bind.getFullName(), new ParamsCall());
					Scalar *sc = new Scalar(globalVarName, fc);
					fc->setScope(funcInitGlobals);
					sc->setScope(funcInitGlobals);
					funcInitGlobals->addChild(sc);
				}
			}

			Load *load = new Load(globalVarName);
			Return *ret = new Return(load);
			ret->setScope(finject);
			load->setScope(finject);
			finject->addChild(ret);
			finject->generate(NULL, NULL, global_alloc);

		} else { // bs_transient
			assert(false && "TODO: implement bs_transient scope.");
		}

		// generate injection function aliases
	    for(const auto & [key, symbol] : bindUserTy->getSymbols()) {
			if (FunctionImpl *impl = dynamic_cast<FunctionImpl*>(symbol)) {
				Identifier destTyIntfName = destinationTyName;
				Node *destIntf = destTyIntfName.getSymbol(this);
				if (destIntf && destIntf->findMember(symbol->getName())) {
					// is a interface member implementation, let add an alias to it
					string to_name = regex_replace(to.getFullName(), regex("\\."), ":") + ":" + symbol->getName();
					Function *implFunc = impl->getLLVMFunction();

					Function *aliasFunc = Function::Create(implFunc->getFunctionType(), Function::ExternalLinkage,
						codeAddrSpace, to_name, mainmodule);
					aliasFunc->setDSOLocal(true);
					aliasFunc->setCallingConv(CallingConv::C);

					auto fblock = BasicBlock::Create(global_context, "", aliasFunc);
					Builder->SetInsertPoint(fblock);
					
					vector<Value*> args;
					for(auto& arg : aliasFunc->args()) {
						//Value *alloc = Builder->CreateAlloca(arg.getType());
						//Value *store = Builder->CreateStore(&arg, alloc);
						//Value *load = Builder->CreateLoad(arg.getType(), alloc);
						args.push_back(&arg);
					}
					
					Value *call = Builder->CreateCall(implFunc, args);
					if (call->getType()->isVoidTy())
						Builder->CreateRetVoid();
					else
						Builder->CreateRet(call);
				}
			}
		}
	}

	funcInitGlobals->generate(NULL, NULL, global_alloc);
}

void Program::generate() {

	// instrumentation passes
	SymbolizeTree st;
	st.visit(*this);

	/*std::fstream fs;
	fs.open("ast", std::fstream::out);
	PrintAstVisitor(fs).visit(p);
	fs.close();*/

	Node *mainFunc = NULL;

	// generate the program!
	for(auto n: children()) {
		if (FunctionImpl *func = dynamic_cast<FunctionImpl*>(n)) {
			if (func->getName() == "main" || func->getName() == "__main") {
				// generate main function after all others
				mainFunc = n;
				continue;
			}
		}

		n->generate(NULL, NULL, global_alloc);

		// if n is a UserType, there is a injection for it?
		/*if (UserType *ut = dynamic_cast<UserType*>(n)) {
			for (auto &[key, itype] : injections) {
				if (itype.first == ut->getName()) {
					const string variableName = ":injectionName__" + itype.first;
					DataType var_dt = buildTypes->getType(itype.first);
					Variable *injectionVariable = new Scalar(variableName, new NullConst(var_dt));
					injectionVariable->setScope(program);
					map_injections[variableName] = injectionVariable;

					program->addSymbol(injectionVariable);
					injectionVariable->generate(NULL, NULL, global_alloc);
					break; //TODO: When implementing transient injection, change here.
				}
			}
		}*/
	}

	if (injections.size() > 0) {
		generateInjectionSetup();

		FunctionCall *fc = new FunctionCall(":injections_init", new ParamsCall());
		fc->setScope(mainFunc);
		mainFunc->addChild(fc, true);
	}

	if (mainFunc)
		mainFunc->generate(NULL, NULL, global_alloc);

	if (debug_info)
		DBuilder->finalize();
}
