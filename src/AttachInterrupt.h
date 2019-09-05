#ifndef __ATTACHINTERRUPT_H__
#define __ATTACHINTERRUPT_H__
#include "Node.h"

class AttachInterrupt: public Node {
private:
	string fname;
	int port;
	int event;
	static Function *fattach;
public:
	AttachInterrupt(int _port, string _fname, int _event) {
		this->fname = _fname;
		this->port = _port;
		this->event = _event;
	}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

		Function *cfunc = (Function*)search_symbol(fname);
		if (cfunc == NULL) {
			yyerrorcpp("Function " + fname + " not defined.");
			return NULL;
		}

		// called func type (the function that is attached to interruption)
		std::vector<Type*> arg_types;
		FunctionType *fcalledtype = FunctionType::get(Type::getVoidTy(global_context),
			arg_types, false);
		
		// setup arduino attachInterrupt function
		if (!fattach) {
			arg_types.clear();
			arg_types.push_back(Type::getInt8Ty(global_context));
			arg_types.push_back(fcalledtype->getPointerTo());
			arg_types.push_back(Type::getInt16Ty(global_context));

			FunctionType *ftype = FunctionType::get(Type::getVoidTy(global_context),
				ArrayRef<Type*>(arg_types), false);

			fattach = Function::Create(ftype, Function::ExternalLinkage, "attachInterrupt", mainmodule);
			fattach->setCallingConv(CallingConv::C);
		}

		vector<Value*> args;
		args.push_back(ConstantInt::get(Type::getInt8Ty(global_context), port));
		args.push_back(cfunc);
		args.push_back(ConstantInt::get(Type::getInt16Ty(global_context), event));

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(fattach, argsRef, "", block);
	}
};

#endif
