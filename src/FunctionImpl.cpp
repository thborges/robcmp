#include "Header.h"

Value *FunctionImpl::generate(Function *, BasicBlock *, BasicBlock *allocblock) {
	auto sym = search_symbol(name);
	if (sym != NULL && !sym->isDeclaration) {
		yyerrorcpp("Function/symbol " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", sym);
		return NULL;
	}

	Function *nfunc;
	Type *xtype = buildTypes->llvmType(tipo);
	if (sym && sym->isDeclaration) {
		//TODO: validateImplementation();
		nfunc = mainmodule->getFunction(name);
	} else {
		std::vector<Type*> arg_types;
		if (parameters->getNumParams() != 0)
			for (int i = 0; i < parameters->getNumParams(); i++)
				arg_types.push_back(buildTypes->llvmType(parameters->getParamType(i)));
		
		FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);
		nfunc = Function::Create(ftype, Function::ExternalLinkage, 1, name, mainmodule);
	}

	nfunc->setDSOLocal(true);
	llvm::AttrBuilder attrs(global_context);
	attrs.addAttribute(Attribute::MinSize);
	
	if (name == "__vectors") { // FIXME: remove after adding functions attributes to language
		nfunc->setSection(".vectors");
	}

	nfunc->setAttributes(llvm::AttributeList().addFnAttributes(global_context, attrs));
	nfunc->setCallingConv(CallingConv::C);

	if (!sym)
		sym = new RobSymbol(nfunc);
	sym->dt = tipo;
	sym->params = parameters;
	sym->isDeclaration = false;
	tabelasym[allocblock][name] = sym;

	DIFile *funit;
	DISubprogram *sp;
	if (debug_info) {
		funit = DBuilder->createFile(RobDbgInfo.cunit->getFilename(), RobDbgInfo.cunit->getDirectory());
		DIScope *fcontext = funit;
		sp = DBuilder->createFunction(fcontext, name, StringRef(), funit, this->getLineNo(),
			getFunctionDIType(), this->getLineNo(), DINode::FlagPrototyped, DISubprogram::SPFlagDefinition);
		nfunc->setSubprogram(sp);
		RobDbgInfo.push_scope(funit, sp);
	}

	BasicBlock *falloc = BasicBlock::Create(global_context, "entry", nfunc);
	BasicBlock *fblock = BasicBlock::Create(global_context, "body", nfunc);
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(falloc);

	unsigned Idx = 0;
	for (auto &Arg : nfunc->args())
	{
		const char *argname = parameters->getParamElement(Idx);
		BasicDataType ptype = parameters->getParamType(Idx);
		
		Arg.setName(argname);
		AllocaInst* variable = Builder->CreateAlloca(buildTypes->llvmType(ptype), 0, argname);
		RobSymbol *rs = new RobSymbol(variable);
		rs->dt = ptype;
		tabelasym[falloc][argname] = rs; 
		StoreInst *val = Builder->CreateStore(&Arg, variable, false);

		if (debug_info) {
			DILocalVariable *d = DBuilder->createParameterVariable(sp, argname, Idx+1, funit,
				this->getLineNo(), buildTypes->diType(ptype), true);
			DBuilder->insertDeclare(variable, d, DBuilder->createExpression(),
				DILocation::get(sp->getContext(), this->getLineNo(), 0, sp),
				falloc);
		}

		Idx++;
	}

	RobDbgInfo.emitLocation(stmts);
	Value *last_block = stmts->generate(nfunc, fblock, falloc);
	if (!last_block)
		last_block = fblock;

	// prevent mallformed block at the end without proper return instruction 
	if (last_block && last_block->getValueID() == Value::BasicBlockVal) {
		BasicBlock *lb = (BasicBlock*)last_block;
		Builder->SetInsertPoint(lb);
		RobDbgInfo.emitLocation(&endfunction);
		if (lb->getTerminator() == NULL) {
			if (!xtype->isVoidTy()) {
				Value *ret = ConstantInt::get(xtype, 0);
				Builder->CreateRet(ret);
			} else
				Builder->CreateRetVoid();
		}
	}

	BranchInst::Create(fblock, falloc);

	if (debug_info)
		RobDbgInfo.pop_scope();
		
	return nfunc;
}

DISubroutineType *FunctionImpl::getFunctionDIType() {
	SmallVector<Metadata*, 8> Tys;
	Tys.push_back(buildTypes->diType(tipo)); // return type
	for(FunctionParam &p : parameters->parameters) {
		Tys.push_back(buildTypes->diType(p.type));
	}
	return DBuilder->createSubroutineType(DBuilder->getOrCreateTypeArray(Tys));
}

bool FunctionImpl::validateImplementation(FunctionDecl *decl) {
	bool result = true;
	const FunctionParams& decl_parameters = decl->getParameters();
	if (parameters->getNumParams() != decl_parameters.getNumParams()) {
		yyerrorcpp(string_format("The number of arguments differs between function declaration(%d) and definition(%d).",
			decl_parameters.getNumParams(), parameters->getNumParams()), this);
		yyerrorcpp("The function declaration is here.", decl);
		result = false;
	}
	int compareno = std::min(parameters->getNumParams(), decl_parameters.getNumParams());
	for(int i = 0; i < compareno; i++) {
		const FunctionParam &p = decl_parameters.parameters[i];
		if (p.type != parameters->parameters[i].type) {
			yyerrorcpp(string_format("Argument %s has distinct type in declaration '%s' and definition '%s'.",
				parameters->parameters[i].name, buildTypes->name(p.type), 
				buildTypes->name(parameters->parameters[i].type)), this);
			yyerrorcpp("The function declaration is here.", decl);
			result = false;
		}
	}
	BasicDataType decl_type = decl->getResultType(NULL, NULL);
	if (tipo != decl_type) {
		yyerrorcpp(string_format("Function return type has distinct type in declaration '%s' and definition '%s'.",
			buildTypes->name(decl_type), buildTypes->name(tipo)), this);
		yyerrorcpp("The function declaration is here.", decl);
		result = false;
	}
	return result;
}
