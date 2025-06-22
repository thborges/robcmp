
#include "FunctionDecl.h"
#include "BackLLVM.h"
#include "FunctionAttributes.h"
#include "Array.h"
#include "Matrix.h"

void FunctionBase::addThisArgument(DataType dt) {
	thisArgDt = dt;
	Variable *fp = new Variable("_this", dt, this->getLoc());
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
		if (!atype) {
			yyerrorcpp(string_format("Type %s for argument %s is not defined.",
				buildTypes->name(dt), parameters->getParamName(i).c_str()), this);
			valid = false;
		} else {
			if (buildTypes->isComplex(dt) || buildTypes->isArrayOrMatrix(dt)) {
				atype = atype->getPointerTo();
			}
			argsty.push_back(atype);
		}
	}
	return valid;
}

void FunctionBase::addParentArgument(DataType dt) {
	parentArgDt = dt;
	Variable *fp = new Variable("_parent", dt, this->getLoc());
	fp->setScope(this);
	parameters->append(fp);
	symbols[fp->getName()] = fp;
}

void FunctionBase::addPseudoParameters() {
	// add a size parameter after each array, or .rows and .cols for matrixes
	std::vector<Variable*> const& vparams = this->parameters->getParameters();
	for (int i = 0; i < vparams.size(); ++i) {
		Variable *p = vparams[i];

		ParamArray *paramArray = dynamic_cast<ParamArray*>(p);
		ParamMatrix *paramMatrix = dynamic_cast<ParamMatrix*>(p);

		if (paramArray || paramMatrix) {
			vector<string> pseudos;
			if (paramMatrix) {
				pseudos.push_back("rows");
				pseudos.push_back("cols");
			} else if (paramArray)
				pseudos.push_back("size");

			for(const string& s: pseudos) {
				//TODO: There is something better than fix this to Int32? Fix here and in FunctionCall::generate
				string spname = p->getName() + "." + s;
				Variable *sp = new Variable(spname, tint32u, p->getLoc()); 
				sp->setPseudoVar(true);
				this->parameters->append(sp);

				// add a pseudo symbol to resolve to pname.s
				p->addSymbol(s, sp);
			}

			// ParamMatrix need to know the number of cols to compute element indexes
			if (paramMatrix) {
				paramMatrix->addSymbol("cols", vparams.back());
			}
		}
	}
}

void FunctionBase::addFunctionAttributes(Function *func) {
	
	//func->addFnAttr(Attribute::MinSize);
	func->addFnAttr("target-cpu", currentTarget().cpu);
	func->addFnAttr("frame-pointer", "all");
	func->addFnAttr("stack-protector-buffer-size", "8");
	
	if (!attributes)
		return;
		
	for(auto &[attr, value] : attributes->getAttributes()) {
		switch (attr) {
			case fa_weak:
				func->setLinkage(GlobalValue::WeakAnyLinkage);
				break;
			case fa_inline:
				func->addFnAttr(Attribute::AlwaysInline);
				break;
			case fa_noinline:
				func->addFnAttr(Attribute::NoInline);
				break;
			case fa_section:
				func->setSection(value);
				break;
			case fa_signal:
				func->addFnAttr("signal");
				break;
			case fa_naked:
				func->addFnAttr(Attribute::Naked);
				func->addFnAttr(Attribute::NoInline);
				break;
			case fa_noopt:
				func->addFnAttr(Attribute::OptimizeNone);
				func->addFnAttr(Attribute::NoInline);
				break;
			default:
				break;
		}
	}
}

Value *FunctionDecl::generate(FunctionImpl*, BasicBlock *, BasicBlock *allocblock) {
	
	if (func)
		return func;

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
	Function *nfunc = Function::Create(ftype, linkage, codeAddrSpace, getFinalName(), mainmodule);
	nfunc->setCallingConv(CallingConv::C);
	addFunctionAttributes(nfunc);

	if (buildTypes->isUnsignedDataType(dt))
		nfunc->addRetAttr(Attribute::ZExt);
	
	unsigned Idx = 0;
	for (auto &Arg : nfunc->args()) {
		Variable *fp = parameters->getParameters()[Idx];
		DataType ptype = fp->getDataType();

		if (buildTypes->isUnsignedDataType(ptype))
			Arg.addAttr(Attribute::ZExt);

		const string& argname = fp->getName();
		if (argname == "_this") {
			thisArg = &Arg;
		} else if (argname == "_parent") {
			parentArg = &Arg;
		}

		Idx++;
	}

	func = nfunc;
	return func;
}

Value* FunctionDecl::getLLVMValue(Node *, FunctionImpl *) {
	if (!func)
		generate(NULL, NULL, global_alloc);
	return func;
}

