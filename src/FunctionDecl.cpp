#include "Header.h"

Value *FunctionDecl::generate(Function *, BasicBlock *, BasicBlock *allocblock) {
	auto sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Function/symbol " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", sym);
		return NULL;
	}

	std::vector<Type*> arg_types;
	if (parameters->getNumParams() != 0)
		for (int i = 0; i < parameters->getNumParams(); i++)
			arg_types.push_back(parameters->getParamType(i));
	
	Type *xtype = robTollvmDataType[tipo];
	FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);

	Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, 0, name, mainmodule);
	nfunc->setDSOLocal(true);
    llvm::AttrBuilder attrs(global_context);
	attrs.addAttribute(llvm::Attribute::MinSize);
    //attrs.addAttribute("stack-protector-buffer-size", llvm::utostr(8));
	//attrs.addAttribute("frame-pointer", "all");
	//attrs.addAttribute("no-trapping-math", "true");
	nfunc->setAttributes(llvm::AttributeList().addFnAttributes(global_context, attrs));

	tabelasym[allocblock][name] = new RobSymbol(nfunc);

	BasicBlock *falloc = BasicBlock::Create(global_context, "entry", nfunc);
	BasicBlock *fblock = BasicBlock::Create(global_context, "body", nfunc);
	unsigned Idx = 0;
	for (auto &Arg : nfunc->args())
	{
		const char *argname = parameters->getParamElement(Idx);
		Arg.setName(argname);
		//Value *valor = search_symbol(argname, fblock, fblock);
		AllocaInst* variable = new AllocaInst(parameters->getParamType(Idx), 0, argname, falloc);
		tabelasym[falloc][argname] = new RobSymbol(variable);
		StoreInst *val = new StoreInst(&Arg, variable, false, fblock);
		Idx++;
	}
	nfunc->setCallingConv(CallingConv::C);

	Value *last_block = stmts->generate(nfunc, fblock, falloc);
	if (!last_block)
		last_block = fblock;

	// prevent mallformed block at the end without proper return instruction 
	if (last_block && last_block->getValueID() == Value::BasicBlockVal) {
		BasicBlock *lb = (BasicBlock*)last_block;
		if (lb->getTerminator() == NULL) {
			if (!xtype->isVoidTy()) {
				Value *ret = ConstantInt::get(Type::getInt8Ty(global_context), 0);
				ret = Coercion::Convert(ret, xtype, lb, this);
				ReturnInst::Create(global_context, ret, lb);
			} else
				ReturnInst::Create(global_context, NULL, lb);
		}
	}

	BranchInst::Create(fblock, falloc);

	return nfunc;
}

