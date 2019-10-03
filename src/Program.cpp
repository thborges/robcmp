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
	}

	void Program::generate() {
		mainmodule = new Module(build_filename, global_context);
	
		FunctionType *ftype = FunctionType::get(Type::getInt16Ty(global_context),
			ArrayRef<Type*>(), false);
		Function *mainfunc = Function::Create(ftype,GlobalValue::ExternalLinkage, "main", mainmodule);

		global_alloc = BasicBlock::Create(global_context, "global");
		mainblock = BasicBlock::Create(global_context, "entry", mainfunc);

		declara_auxiliary_c_funcs();

		// call Arduino init
		#ifdef ENABLE_ARDUINO
		std::vector<Value*> args;
		ArrayRef<Value*> argsRef(args);
		/*CallInst *call =*/ CallInst::Create(init, argsRef, "", mainblock);
		#endif

		// generate the program!
		Value *b = stmts->generate(mainfunc, mainblock, global_alloc);
		if (b->getValueID() == Value::BasicBlockVal)  {
			mainblock = (BasicBlock*)b;
		}

		Int16 ret(0);
		Value *retv = ret.generate(mainfunc, mainblock, mainblock);
		ReturnInst::Create(global_context, retv, mainblock);
	}
