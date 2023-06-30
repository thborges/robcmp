#include "Header.h"

Value *FunctionDeclExtern::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	Value *sym = search_symbol(name);
	if (sym != NULL) {
		yyerrorcpp("Function " + name + " already defined.");
		return NULL;
	}

	std::vector<Type*> arg_types;
	if (parameters->getNumParams() != 0)
		for (int i = 0; i < parameters->getNumParams(); i++)
			arg_types.push_back(parameters->getParamType(i));
	
	/* TODO: Refactor (here and in FunctionDecl.cpp) */
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
	nfunc->setCallingConv(CallingConv::C);
	tabelasym[mainblock][name] = nfunc;

	return nfunc;
}

