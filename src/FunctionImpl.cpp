#include "FunctionImpl.h"
#include "BackLLVM.h"
#include "semantic/Visitor.h"

FunctionImpl::FunctionImpl(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts,
	location_t loc, location_t ef, bool constructor) :
	FunctionBase(dt, name, fp, std::move(stmts), loc, constructor), endfunction(ef) {
	this->declaration = false;
	funit = RobDbgInfo.currFile();

	for(auto p: fp->getParameters()) {
		symbols[p->getName()] = p;
		p->setScope(this);
	}
}

bool FunctionImpl::preGenerate() {
	preGenerated = true;

	Node *symbol = findSymbol(name);
	FunctionDecl *fsymbol = dynamic_cast<FunctionDecl*>(symbol);
	if (symbol != NULL && symbol != this && fsymbol != NULL && !fsymbol->isDeclaration()) {
		yyerrorcpp("Function/symbol " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", symbol);
		return false;
	}

	Type *xtype = buildTypes->llvmType(dt);
	if (returnIsPointer)
		xtype = xtype->getPointerTo();

	if (fsymbol) {
		validateImplementation(fsymbol);
		func = mainmodule->getFunction(name);
		func->setName(getFinalName());
	} else {
		std::vector<Type*> arg_types;
		if (!validateAndGetArgsTypes(arg_types))
			return false;
		
		FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);
		func = Function::Create(ftype, linkage, codeAddrSpace, getFinalName(), mainmodule);
	}

#ifdef __MINGW64__
	if (name == "main")
		func->setName("__main");
#endif

	addFunctionAttributes(func);
	func->setCallingConv(CallingConv::C);

	if (buildTypes->isUnsignedDataType(dt))
		func->addRetAttr(Attribute::ZExt);

	if (debug_info && !declaration) {
		sp = DBuilder->createFunction(funit, getFinalName(), StringRef(), funit,
			this->getLineNo(), getFunctionDIType(), this->getLineNo(), DINode::FlagZero, 
			DISubprogram::SPFlagDefinition);
		func->setSubprogram(sp);
		RobDbgInfo.push_scope(sp);
	}

	if (isExternal())
		return true;

	falloc = BasicBlock::Create(global_context, "", func);
	fblock = BasicBlock::Create(global_context, "body", func);
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(falloc);

	unsigned Idx = 0;
	for (auto &Arg : func->args()) {
		Variable *fp = parameters->getParameters()[Idx];
		DataType ptype = fp->getDataType();
		const string& argname = fp->getName();
		Arg.setName(argname);

		if (buildTypes->isUnsignedDataType(ptype))
			Arg.addAttr(Attribute::ZExt);

		Type *talloc = buildTypes->llvmType(ptype);
		if (buildTypes->isComplex(ptype) || buildTypes->isArrayOrMatrix(ptype)) {
			talloc = talloc->getPointerTo();
			fp->setPointerToPointer(true);
		}
		Value *variable = Builder->CreateAlloca(talloc, dataAddrSpace, 0, argname);
		
		if (argname == "_this") {
			thisArg = variable;
		} else if (argname == "_parent") {
			parentArg = variable;
		}
		
		fp->setAlloca(variable);
		
		Builder->CreateStore(&Arg, variable, false);

		if (debug_info) {
			DIType *dit = buildTypes->diType(ptype);
			if (buildTypes->isComplex(ptype) || buildTypes->isArrayOrMatrix(ptype))
				dit = buildTypes->diPointerType(ptype);

			DILocalVariable *d = DBuilder->createParameterVariable(sp, argname, Idx+1, funit,
				this->getLineNo(), dit, true);
			DBuilder->insertDeclare(variable, d, RobDbgInfo.getFixedOffsetExpression(),
				DILocation::get(sp->getContext(), this->getLineNo(), 0, sp),
				falloc);
		}

		Idx++;
	}

	if (debug_info)
		RobDbgInfo.pop_scope();

	return true;
}

Value *FunctionImpl::generate(FunctionImpl *, BasicBlock *, BasicBlock *allocblock) {

	if (!preGenerated) {
		if (!preGenerate())
			return NULL;
	} 

	if (isExternal() || isDeclaration()) //can be declaration when came from USEparser
		return NULL;

	if (debug_info) {
		RobDbgInfo.push_scope(sp);
		RobDbgInfo.emitLocation(this);
	}
	
	Value *last_block = generateChildren(this, fblock, falloc);
	if (!last_block)
		last_block = fblock;

	// prevent mallformed block at the end without proper return instruction 
	if (last_block->getValueID() == Value::BasicBlockVal) {
		BasicBlock *lb = (BasicBlock*)last_block;
		Builder->SetInsertPoint(lb);
		RobDbgInfo.emitLocation(&endfunction);
		if (lb->sizeWithoutDebug() == 0 && !lb->hasNPredecessorsOrMore(1) &&
			lb != fblock) {
			lb->eraseFromParent();

		} else if (lb->getTerminator() == NULL) {
			Type *xtype = buildTypes->llvmType(dt);
			if (!xtype->isVoidTy()) {
				yyerrorcpp("Missing return statement in function " + name, &endfunction);
			} else
				Builder->CreateRetVoid();
		}
	}

	if (falloc->empty())
		falloc->removeFromParent();
	else
		BranchInst::Create(fblock, falloc);

	if (debug_info)
		RobDbgInfo.pop_scope();

	return func;
}

DISubroutineType *FunctionImpl::getFunctionDIType() {
	SmallVector<Metadata*, 8> Tys;
	Tys.push_back(buildTypes->diType(dt)); // return type
	for(Variable *p : parameters->getParameters()) {
		Tys.push_back(buildTypes->diType(p->getDataType()));
	}
	return DBuilder->createSubroutineType(DBuilder->getOrCreateTypeArray(Tys));
}

bool FunctionImpl::validateImplementation(FunctionDecl *decl) {
	bool result = true;
	FunctionParams& decl_parameters = decl->getParameters();
	unsigned pnum_decl = decl_parameters.getNumCodedParams();
	unsigned pnum_impl = parameters->getNumCodedParams();
	if (pnum_impl != pnum_decl) {
		yyerrorcpp(string_format("The number of arguments differs between function declaration(%d) and definition(%d).",
			pnum_decl, pnum_impl), this);
		yywarncpp("The function declaration is here.", decl);
		result = false;
	}
	int compareno = std::min(pnum_impl, pnum_decl);
	for(int i = 0; i < compareno; i++) {
		Variable *p = decl_parameters.getParameters()[i];
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

Node* FunctionImpl::accept(Visitor& v) {
	return v.visit(*this);
}

Value* FunctionImpl::getLLVMValue(Node *, FunctionImpl *) {
	if (!preGenerated)
		preGenerate();
	return func;
}
