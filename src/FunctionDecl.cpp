#include "Header.h"

Value *FunctionDecl::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Function " + name + " already defined.");
		return NULL;
	}

	std::vector<Type*> arg_types;
	if (parameters->getNumParams() != 0)
		for (int i = 0; i < parameters->getNumParams(); i++)
			arg_types.push_back(parameters->getParamType(i));
	
	Type *xtype;
	switch(tipo){
		case 0:
				xtype = Type::getVoidTy(global_context);
			break;			
		case 1:
				xtype = Type::getInt1Ty(global_context);
			break;			
		case 2:
				xtype = Type::getInt8Ty(global_context);
			break;			
		case 3:
				xtype = Type::getInt16Ty(global_context);
			break;			
		case 4:
				xtype = Type::getInt32Ty(global_context);
			break;			
		case 5:
				xtype = Type::getInt64Ty(global_context);
			break;			
		case 6:
				xtype = Type::getInt128Ty(global_context);
			break;			
		case 7:
				xtype = Type::getHalfTy(global_context);
			break;			
		case 8:
				xtype = Type::getFloatTy(global_context);
			break;			
		case 9:
				xtype = Type::getDoubleTy(global_context);
			break;			
		case 10:
				xtype = Type::getFP128Ty(global_context);
			break;			
	}

	FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);

	Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, name, mainmodule);
	tabelasym[mainblock][name] = nfunc;

	BasicBlock *falloc = BasicBlock::Create(global_context, "entry", nfunc);
	BasicBlock *fblock = BasicBlock::Create(global_context, "body", nfunc);
	unsigned Idx = 0;
	for (auto &Arg : nfunc->args())
	{
		const char *argname = parameters->getParamElement(Idx);
		Arg.setName(argname);
		//Value *valor = search_symbol(argname, fblock, fblock);
		AllocaInst* variable = new AllocaInst(parameters->getParamType(Idx), 0, argname, falloc);
		tabelasym[falloc][argname] = variable;
		StoreInst *val = new StoreInst(&Arg, variable, argname, false, fblock);
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
				ret = Coercion::Convert(ret, xtype, lb);
				ReturnInst::Create(global_context, ret, lb);
			} else
				ReturnInst::Create(global_context, NULL, lb);
		}
	}

	BranchInst::Create(fblock, falloc);

	return nfunc;
}

