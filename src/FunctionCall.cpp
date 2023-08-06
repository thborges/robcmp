#include "FunctionCall.h"
#include "Cast.h"
#include "FunctionDecl.h"
#include "FunctionImpl.h"
#include "HeaderGlobals.h"
#include "Coercion.h"
#include "Load.h"
#include "Visitor.h"
#include "BackLLVM.h"

DataType FunctionCall::getDataType() {
	
	if (dt == BuildTypes::undefinedType) {
		// is a cast?
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

void FunctionCall::loadFunctionStem(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

}

Value *FunctionCall::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	string name = ident.getFullName();

	// check if it is a cast call
	DataType adt = buildTypes->getType(name);
	if (adt != BuildTypes::undefinedType) {
		dt = adt;
		unsigned p = parameters->getNumParams();
		
		// call with only one parameter is a cast
		if (p == 1) {
			Cast ca(dt, parameters->getParamElement(0));
			return ca.generate(func, block, allocblock);

		} else if (p == 0) { // it's a constructor
			RobDbgInfo.emitLocation(this);
			
			// alloc
			Value *var = leftValue;
			if (leftValue == NULL) {
				Builder->SetInsertPoint(allocblock);
				var = Builder->CreateAlloca(buildTypes->llvmType(dt), globalAddrSpace, 0, leftName);
			}
			vector<Value*> args;
			args.push_back(var);

			// call #init
			Node *type = findSymbol(name);
			Node *fsymbol = type->findMember("init");
			FunctionImpl *initfunc = dynamic_cast<FunctionImpl*>(fsymbol);
			Builder->SetInsertPoint(block);
			Builder->CreateCall(initfunc->getLLVMFunction(), ArrayRef<Value*>(args));
			return var;
		}
	}

	if (!symbol)
		symbol = ident.getSymbol(getScope(), false);

	if (symbol == NULL) {
		yyerrorcpp("Function " + name + " not defined.", this);
		return NULL;
	}

	FunctionBase *fsymbol = dynamic_cast<FunctionBase*>(symbol);
	Function *cfunc = dyn_cast<Function>(symbol->getLLVMValue(func));
	if (fsymbol == NULL || cfunc == NULL) {
		yyerrorcpp("Symbol " + name + " is not a function.", this);
		return NULL;
	}

	dt = fsymbol->getDataType();

	bool this_param = false;
	Value *stem = NULL;
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *n = istem.getSymbol(getScope());
		stem = n->getLLVMValue(func);
		
		// TODO: When accessing a.x.func(), need to load a and gep x
		//Load loadstem(ident.getStem());
		//loadstem.setParent(this->parent);
		//stem = loadstem.generate(func, block, allocblock);
		
		this_param = true;
	}

	if (fsymbol->getNumParams() != parameters->getNumParams() + this_param) {
		yyerrorcpp(string_format("Function %s has %d argument(s) but was called with %d.",
			name.c_str(), fsymbol->getNumParams(), parameters->getNumParams()), this);
		yywarncpp("The function declaration is here.", symbol);
		return NULL;
	}

	vector<Value*> args;
	for (int i = 0; i < parameters->getNumParams(); i++){
		Value *valor = parameters->getParamElement(i)->generate(func, block, allocblock);
		DataType pdt = fsymbol->getParameters().getParamType(i);
		if (!buildTypes->isComplex(pdt)) {
			//TODO: we don't support cohercion between user types yet
			Type *pty = buildTypes->llvmType(pdt);
			valor = Coercion::Convert(valor, pty, block, this);
		}
		args.push_back(valor);
	}

	if (this_param)
		args.push_back(stem);

	ArrayRef<Value*> argsRef(args);

	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	return Builder->CreateCall(cfunc, argsRef);
}

void FunctionCall::accept(Visitor& v) {
	v.visit(*this);
}
