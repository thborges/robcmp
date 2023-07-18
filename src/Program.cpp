#include "Header.h"

Program::Program(Stmts *stmts) {
	this->stmts = stmts;
	node_children.reserve(1);
	node_children.push_back(stmts);
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

Value *Program::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	return NULL;
}

void Program::generate() {

	// conversion between robcmp data types to llvm data types
	robTollvmDataType[tvoid]    = Type::getVoidTy(global_context);
	robTollvmDataType[tbool]    = Type::getInt1Ty(global_context);
	robTollvmDataType[tchar]    = Type::getInt8Ty(global_context);
	robTollvmDataType[tint8]    = Type::getInt8Ty(global_context);
	robTollvmDataType[tint16]   = Type::getInt16Ty(global_context);
	robTollvmDataType[tint32]   = Type::getInt32Ty(global_context);
	robTollvmDataType[tint64]   = Type::getInt64Ty(global_context);
	robTollvmDataType[tint8u]   = Type::getInt8Ty(global_context);
	robTollvmDataType[tint16u]  = Type::getInt16Ty(global_context);
	robTollvmDataType[tint32u]  = Type::getInt32Ty(global_context);
	robTollvmDataType[tint64u]  = Type::getInt64Ty(global_context);
	robTollvmDataType[tfloat]   = Type::getFloatTy(global_context);
	robTollvmDataType[tdouble]  = Type::getDoubleTy(global_context);
	robTollvmDataType[tldouble] = Type::getFP128Ty(global_context);

	mainmodule = new Module(build_filename, global_context);
	Builder = make_unique<IRBuilder<>>(global_context);

	if (debug_info) {
		mainmodule->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);
		mainmodule->addModuleFlag(Module::Warning, "Dwarf Version", 2);
		DBuilder = make_unique<DIBuilder>(*mainmodule);
		RobDbgInfo.cunit = DBuilder->createCompileUnit(dwarf::DW_LANG_C,
			DBuilder->createFile(build_filename, std::filesystem::current_path().string()),
			"Robcmp", false, "", 0);
		for(int t = 0; t < __ldt_last; t++) {
			RobDbgInfo.types[t] = DBuilder->createBasicType(
				LanguageDataTypeNames[t],
				LanguageDataTypeBitWidth[t],
				LanguageDataTypeDwarfEnc[t]
			);
		}
	}

	global_alloc = BasicBlock::Create(global_context, "global");

	// generate the program!
	stmts->generate(NULL, NULL, global_alloc);

	if (debug_info)
		DBuilder->finalize();
}
