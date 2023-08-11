#include "FunctionImpl.h"
#include "Visitor.h"
#include "BackLLVM.h"

FunctionImpl::FunctionImpl(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts,
	location_t ef, bool constructor) :
	FunctionBase(dt, name, fp, std::move(stmts), constructor) {
	this->declaration = false;
	this->endfunction = ef;

	// params needs to be the first inserted children
	// to fill the symbols table prior to their use in stmts
	for(auto p: fp->getParameters()) {
		node_children.insert(node_children.begin(), p);
	}	
}

Value *FunctionImpl::generate(FunctionImpl *, BasicBlock *, BasicBlock *allocblock) {
	
	Node *symbol = findSymbol(name);
	FunctionDecl *fsymbol = dynamic_cast<FunctionDecl*>(symbol);
	if (symbol != NULL && symbol != this && fsymbol != NULL && !fsymbol->isDeclaration()) {
		yyerrorcpp("Function/symbol " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", symbol);
		return NULL;
	}

	Type *xtype = buildTypes->llvmType(dt);
	if (fsymbol) {
		validateImplementation(fsymbol);
		func = mainmodule->getFunction(name);
		func->setName(getFinalName());
	} else {
		std::vector<Type*> arg_types;
		if (!validateAndGetArgsTypes(arg_types))
			return NULL;
		
		FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);
		func = Function::Create(ftype, Function::ExternalLinkage, codeAddrSpace, getFinalName(), mainmodule);
	}

#ifdef __MINGW64__
	if (name == "main")
		func->setName("__main");
#endif
	
	if (isExternal())
		return NULL;

	func->setDSOLocal(true);
	llvm::AttrBuilder attrs(global_context);
	//attrs.addAttribute(Attribute::MinSize);
	attrs.addAttribute("target-cpu", currentTarget.cpu);
	attrs.addAttribute("frame-pointer", "all");
	attrs.addAttribute("stack-protector-buffer-size", "8");
	
	if (name == "init") // inline constructors
		attrs.addAttribute(Attribute::InlineHint);
	
	if (name == "__vectors") { // FIXME: remove after adding functions attributes to language
		func->setSection(".vectors");
	}
	
	func->setAttributes(llvm::AttributeList().addFnAttributes(global_context, attrs));
	func->setCallingConv(CallingConv::C);

	DIFile *funit;
	DISubprogram *sp;
	if (debug_info) {
		funit = DBuilder->createFile(RobDbgInfo.cunit->getFilename(), RobDbgInfo.cunit->getDirectory());
		DIScope *fcontext = funit;
		sp = DBuilder->createFunction(fcontext, getFinalName(), StringRef(), funit, this->getLineNo(),
			getFunctionDIType(), this->getLineNo(), DINode::FlagZero, DISubprogram::SPFlagDefinition);
		func->setSubprogram(sp);
		RobDbgInfo.push_scope(funit, sp);
	}

	BasicBlock *falloc = BasicBlock::Create(global_context, "entry", func);
	BasicBlock *fblock = BasicBlock::Create(global_context, "body", func);
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(falloc);

	unsigned Idx = 0;
	for (auto &Arg : func->args()) {
		FunctionParam *fp = parameters->getParameters()[Idx];
		DataType ptype = fp->getDataType();
		const string& argname = fp->getName();

		Arg.setName(argname);

		Value *variable = &Arg;
		if (!buildTypes->isComplex(ptype))
			variable = Builder->CreateAlloca(buildTypes->llvmType(ptype), dataAddrSpace, 0, argname);
		
		if (argname == "#this") {
			thisArg = variable;
		}
		
		fp->setAlloca(variable);
		
		if (!buildTypes->isComplex(ptype))
			Builder->CreateStore(&Arg, variable, false);

		if (debug_info) {
			DILocalVariable *d = DBuilder->createParameterVariable(sp, argname, Idx+1, funit,
				this->getLineNo(), buildTypes->diType(ptype), true);
			DBuilder->insertDeclare(variable, d, RobDbgInfo.getFixedOffsetExpression(),
				DILocation::get(sp->getContext(), this->getLineNo(), 0, sp),
				falloc);
		}

		Idx++;
	}

	Value *last_block = generateChildren(this, fblock, falloc);
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

	return func;
}

DISubroutineType *FunctionImpl::getFunctionDIType() {
	SmallVector<Metadata*, 8> Tys;
	Tys.push_back(buildTypes->diType(dt)); // return type
	for(FunctionParam *p : parameters->getParameters()) {
		Tys.push_back(buildTypes->diType(p->getDataType()));
	}
	return DBuilder->createSubroutineType(DBuilder->getOrCreateTypeArray(Tys));
}

bool FunctionImpl::validateImplementation(FunctionDecl *decl) {
	bool result = true;
	FunctionParams& decl_parameters = decl->getParameters();
	if (parameters->getNumParams() != decl_parameters.getNumParams()) {
		yyerrorcpp(string_format("The number of arguments differs between function declaration(%d) and definition(%d).",
			decl_parameters.getNumParams(), parameters->getNumParams()), this);
		yywarncpp("The function declaration is here.", decl);
		result = false;
	}
	int compareno = std::min(parameters->getNumParams(), decl_parameters.getNumParams());
	for(int i = 0; i < compareno; i++) {
		FunctionParam *p = decl_parameters.getParameters()[i];
		if (p->getDataType() != parameters->getParamType(i)) {
			yyerrorcpp(string_format("Argument %s has distinct type in declaration '%s' and definition '%s'.",
				parameters->getParamName(i).c_str(), buildTypes->name(p->getDataType()), 
				buildTypes->name(parameters->getParamType(i))), this);
			yywarncpp("The function declaration is here.", decl);
			result = false;
		}
	}
	DataType decl_type = decl->getDataType();
	if (dt != decl_type) {
		yyerrorcpp(string_format("Function return type has distinct type in declaration '%s' and definition '%s'.",
			buildTypes->name(decl_type), buildTypes->name(dt)), this);
		yywarncpp("The function declaration is here.", decl);
		result = false;
	}
	return result;
}

void FunctionImpl::addThisArgument(DataType dt) {
	thisArgDt = dt;
	parameters->append(new FunctionParam("#this", dt));
}

void FunctionImpl::accept(Visitor& v) {
	v.visit(*this);
}
