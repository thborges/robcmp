#include "Program.h"
#include "SymbolizeTree.h"
#include "BackLLVM.h"

Program::Program() {
	mainmodule = new Module(this->getFile(), global_context);
	Builder = make_unique<IRBuilder<>>(global_context);

	if (debug_info) {
		mainmodule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
		mainmodule->addModuleFlag(Module::Warning, "Dwarf Version", 4);
		DBuilder = make_unique<DIBuilder>(*mainmodule);
		RobDbgInfo.cunit = DBuilder->createCompileUnit(dwarf::DW_LANG_C,
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

void Program::generate() {

	// instrumentation passes
	SymbolizeTree st;
	st.visit(*this);

	/*std::fstream fs;
	fs.open("ast", std::fstream::out);
	PrintAstVisitor(fs).visit(p);
	fs.close();*/

	// generate the program!
	for(auto n: children())
		n->generate(NULL, NULL, global_alloc);

	if (debug_info)
		DBuilder->finalize();
}
