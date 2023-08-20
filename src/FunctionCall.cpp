#include "FunctionCall.h"
#include "Cast.h"
#include "FunctionDecl.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "Coercion.h"
#include "Load.h"
#include "Visitor.h"
#include "BackLLVM.h"
#include "UserType.h"

DataType FunctionCall::getDataType() {
	
	if (dt == BuildTypes::undefinedType) {
		// is a cast or constructor?
		dt = buildTypes->getType(ident.getFullName());
		if (parameters->getNumParams() <= 1 && dt != BuildTypes::undefinedType) {
			return dt;
		}

		if (!symbol)
			symbol = ident.getSymbol(getScope());

		if (symbol)
			dt = symbol->getDataType();
	}
	return dt;
}

Value *FunctionCall::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	RobDbgInfo.emitLocation(this);
	string name = ident.getFullName();

	// check if it is a cast call
	DataType adt = buildTypes->getType(name);
	if (adt != BuildTypes::undefinedType) {
		dt = adt;
		unsigned p = parameters->getNumParams();
		
		// call with only one parameter is a cast
		if (p == 1) {
			Node *param = parameters->getParamElement(0);
			Cast ca(dt, param);
			ca.setScope(this);
			if (!param->getScope())
				param->setScope(&ca);
			return ca.generate(func, block, allocblock);

		} else if (p == 0) { // it's a constructor			
			// alloc
			Builder->SetInsertPoint(block);
			Value *var = leftValue->getLLVMValue(func);
			if (var == NULL) {
				Builder->SetInsertPoint(allocblock);
				var = Builder->CreateAlloca(buildTypes->llvmType(dt), dataAddrSpace, 0, 
					leftValue->getName());
				leftValue->setAlloca(var);
				leftValue->setDataType(dt);
				if (debug_info)
					RobDbgInfo.declareVar(leftValue, var, allocblock);
			}
			vector<Value*> args;
			args.push_back(var);

			// call #init
			Node *type = findSymbol(name);
			if (!type)
				return NULL;
			Node *fsymbol = type->findMember("init");
			if (!fsymbol)
				return NULL;
			FunctionBase *initfunc = dynamic_cast<FunctionBase*>(fsymbol);
			
			Builder->SetInsertPoint(block);

			if (initfunc->needsParent()) {
				Type *thisTy = buildTypes->llvmType(func->getThisArgDt());
				Value *ptr = Builder->CreateLoad(thisTy->getPointerTo(), func->getThisArg(), "derefthis");
				args.push_back(ptr);
			}

			CallInst *c = Builder->CreateCall(initfunc->getLLVMFunction(), ArrayRef<Value*>(args));
			return NULL;
		}
	}

	if (!symbol)
		symbol = ident.getSymbol(getScope(), false);

	if (symbol == NULL) {
		yyerrorcpp("Function " + name + " not defined.", this);
		return NULL;
	}

	FunctionBase *fsymbol = dynamic_cast<FunctionBase*>(symbol);
	if (fsymbol == NULL) {
		yyerrorcpp("Symbol " + name + " is not a function.", this);
		return NULL;
	}

	if (fsymbol->getNumCodedParams() != parameters->getNumParams()) {
		yyerrorcpp(string_format("Function %s has %d argument(s) but was called with %d.",
			name.c_str(), fsymbol->getNumCodedParams(), 
			parameters->getNumParams()), this);
		yywarncpp("The function declaration is here.", symbol);
		return NULL;
	}

	dt = fsymbol->getDataType();

	Value *stem = func->getThisArg();
	DataType stemdt = func->getThisArgDt();
	bool stemIsPointerToPointer = false;

	Builder->SetInsertPoint(block);
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *n = istem.getSymbol(getScope());
		stem = n->getLLVMValue(func);
		stemdt = n->getDataType();
		stemIsPointerToPointer = n->isPointerToPointer();
		
		// TODO: When accessing a.x.func(), need to load a and gep x
		//Load loadstem(ident.getStem());
		//loadstem.setParent(this->parent);
		//stem = loadstem.generate(func, block, allocblock);
	}

	vector<Value*> args;
	for (int i = 0; i < parameters->getNumParams(); i++){
		Value *valor = parameters->getParamElement(i)->generate(func, block, allocblock);
		if (!valor)
			return NULL;
			
		DataType pdt = fsymbol->getParameters().getParamType(i);
		if (buildTypes->isInterface(pdt)) {
			valor = Builder->CreateLoad(valor->getType()->getPointerTo(), valor, "defer");
		} else if (!buildTypes->isComplex(pdt)) {
			//TODO: we don't support cohercion between user types yet
			Type *pty = buildTypes->llvmType(pdt);
			valor = Coercion::Convert(valor, pty, block, this);
		}
		args.push_back(valor);
	}

	// this parameter
	if (stem) {
		if (stemIsPointerToPointer)
			stem = Builder->CreateLoad(stem->getType()->getPointerTo(), stem, "defer");
		args.push_back(stem);
	}

	ArrayRef<Value*> argsRef(args);

	Builder->SetInsertPoint(allocblock);
	Value *vfunc = symbol->getLLVMValue(func);
	Function *cfunc = dyn_cast<Function>(vfunc);

	Builder->SetInsertPoint(block);
	return Builder->CreateCall(cfunc, argsRef);
}

void FunctionCall::accept(Visitor& v) {
	v.visit(*this);
}
