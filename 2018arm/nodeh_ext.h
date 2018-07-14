
#include "../node.h"

class ServoGoto: public Node {
private:
	Node *pos;
	static Function *fservo_goto;
public:
	ServoGoto(Node *position): pos(position) {}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// value for the two parameters
		vector<Value*> args;
		args.push_back(pos->generate(func, block, allocblock));

		// get the function signature
		if (!fservo_goto) {
			
			vector<Type*> arg_types;
			arg_types.push_back(Type::getInt16Ty(global_context));
			FunctionType *ftype = FunctionType::get(Type::getVoidTy(global_context), ArrayRef<Type*>(arg_types), false);
			fservo_goto = Function::Create(ftype, Function::ExternalLinkage, "servo_goto", mainmodule);
			fservo_goto->setCallingConv(CallingConv::C);
		}

		// generate code to call servo_goto function
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(fservo_goto, argsRef, "", block);
	}
};

class StepperGoto: public Node {
private:
	int stp;
	Node *pos;
	static Function *fstepper_goto;
public:
	StepperGoto(int stepper, Node *position): stp(stepper), pos(position) {}

	virtual Value *generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// value for the two parameters
		Int16 nstp(stp);

		vector<Value*> args;
		args.push_back(nstp.generate(func, block, allocblock));
		args.push_back(pos->generate(func, block, allocblock));

		// get the function signature
		if (!fstepper_goto) {
			
			vector<Type*> arg_types;
			arg_types.push_back(Type::getInt16Ty(global_context));
			arg_types.push_back(Type::getInt16Ty(global_context));
			FunctionType *ftype = FunctionType::get(Type::getVoidTy(global_context), ArrayRef<Type*>(arg_types), false);
			fstepper_goto = Function::Create(ftype, Function::ExternalLinkage, "stepper_goto", mainmodule);
			fstepper_goto->setCallingConv(CallingConv::C);
		}

		// generate code to call stepper_goto function
		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(fstepper_goto, argsRef, "", block);
	}
};

Function *StepperGoto::fstepper_goto = NULL;
Function *ServoGoto::fservo_goto = NULL;

