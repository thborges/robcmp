
#include "FunctionDecl.h"
#include "BackLLVM.h"

void FunctionBase::addThisArgument(DataType dt) {
	thisArgDt = dt;
	Variable *fp = new Variable(":this", dt);
	fp->setScope(this);
	parameters->append(fp);
	symbols[fp->getName()] = fp;
}

bool FunctionBase::validateAndGetArgsTypes(std::vector<Type*> &argsty) {
	bool valid = true;
	Type *xtype = buildTypes->llvmType(dt);
	if (!xtype) {
		yyerrorcpp(string_format("Type %s is not defined.", buildTypes->name(dt)), this);
		valid = false;
	}
	for (int i = 0; i < parameters->getParameters().size(); i++) {
		DataType dt = parameters->getParamType(i);
		Type *atype = buildTypes->llvmType(dt);
		if (buildTypes->isComplex(dt) || buildTypes->isArrayOrMatrix(dt)) {
			atype = atype->getPointerTo();
		}
		if (!atype) {
			yyerrorcpp(string_format("Type %s for argument %s is not defined.",
				buildTypes->name(dt), parameters->getParamName(i).c_str()), this);
			valid = false;
		} else {
			argsty.push_back(atype);
		}
	}
	return valid;
}

void FunctionBase::addParentArgument(DataType dt) {
	parentArgDt = dt;
	Variable *fp = new Variable(":parent", dt);
	fp->setScope(this);
	parameters->append(fp);
	symbols[fp->getName()] = fp;
}

Value *FunctionDecl::generate(FunctionImpl*, BasicBlock *, BasicBlock *allocblock) {
	
	Node *symbol = findSymbol(name);
	if (symbol != NULL && symbol != this) {
		yyerrorcpp("Function/symbol " + name + " already defined.", this);
		yyerrorcpp(name + " was first defined here.", symbol);
		return NULL;
	}

	std::vector<Type*> arg_types;
	if (!validateAndGetArgsTypes(arg_types))
		return NULL;

	Type *xtype = buildTypes->llvmType(dt);
	if (returnIsPointer)
		xtype = xtype->getPointerTo();
	
	FunctionType *ftype = FunctionType::get(xtype, ArrayRef<Type*>(arg_types), false);
	Function *nfunc = Function::Create(ftype, Function::ExternalLinkage, codeAddrSpace, getFinalName(), mainmodule);
	nfunc->setDSOLocal(true);
	nfunc->setCallingConv(CallingConv::C);

	func = nfunc;
	return func;
}
