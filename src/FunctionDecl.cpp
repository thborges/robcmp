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
			arg_types.push_back(robTollvmDataType[parameters->getParamType(i)]);
	
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

	RobSymbol *rs = new RobSymbol(nfunc);
	rs->dt = tipo;
	tabelasym[allocblock][name] = rs;

	DIFile *funit;
	DISubprogram *sp;
	if (debug_info) {
		funit = DBuilder->createFile(RobDbgInfo.cunit->getFilename(), RobDbgInfo.cunit->getDirectory());
		DIScope *fcontext = funit;
		sp = DBuilder->createFunction(fcontext, name, StringRef(), funit, this->lineno,
			getFunctionDIType(), this->lineno, DINode::FlagPrototyped, DISubprogram::SPFlagDefinition);
		nfunc->setSubprogram(sp);
		RobDbgInfo.push_scope(funit, sp);
		RobDbgInfo.emitLocation(nullptr);
	}

	BasicBlock *falloc = BasicBlock::Create(global_context, "entry", nfunc);
	BasicBlock *fblock = BasicBlock::Create(global_context, "body", nfunc);
	Builder->SetInsertPoint(falloc);
	unsigned Idx = 0;
	for (auto &Arg : nfunc->args())
	{
		const char *argname = parameters->getParamElement(Idx);
		LanguageDataType ptype = parameters->getParamType(Idx);
		
		Arg.setName(argname);
		AllocaInst* variable = Builder->CreateAlloca(robTollvmDataType[ptype], 0, argname );
		RobSymbol *rs = new RobSymbol(variable);
		rs->dt = ptype;
		tabelasym[falloc][argname] = rs; 
		StoreInst *val = Builder->CreateStore(&Arg, variable, false);

		if (debug_info) {
			DILocalVariable *d = DBuilder->createParameterVariable(sp, argname, Idx+1, funit,
				this->lineno, RobDbgInfo.types[ptype], true);
			DBuilder->insertDeclare(variable, d, DBuilder->createExpression(),
				DILocation::get(sp->getContext(), this->lineno, 0, sp),
				falloc);
		}

		Idx++;
	}
	nfunc->setCallingConv(CallingConv::C);

	if (debug_info)
		RobDbgInfo.emitLocation(stmts);

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

	if (debug_info)
		RobDbgInfo.pop_scope();
		
	return nfunc;
}

DISubroutineType *FunctionDecl::getFunctionDIType() {
	SmallVector<Metadata*, 8> Tys;
	Tys.push_back(RobDbgInfo.types[tipo]); // return type
	for(FunctionParam &p : parameters->parameters) {
		Tys.push_back(RobDbgInfo.types[p.type]);
	}
	return DBuilder->createSubroutineType(DBuilder->getOrCreateTypeArray(Tys));
}
