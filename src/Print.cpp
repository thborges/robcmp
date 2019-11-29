#include "Header.h"

	Value *Print::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		vector<Value*> args;

		Value *lexp = expr->generate(func, block, allocblock);
		char cty1 = -1;
		if (lexp != NULL) {
			Type *ty1 = lexp->getType();
			if (ty1->isIntegerTy())
				cty1 = 0;
			else if (ty1->isFloatTy())
				cty1 = 1;
			else if (ty1->isArrayTy())
				cty1 = 2;
		}
		/* TODO */
		if (cty1 == -1) {
			yyerrorcpp("Type not supported by print.");
			return NULL;
		}

		Int8 prt(cty1);
		args.push_back(prt.generate(func, block, allocblock));
		
		AllocaInst *ptr_aux = new AllocaInst(lexp->getType(), 0, "prntaux", block);
		/*StoreInst *st = */ new StoreInst(lexp, ptr_aux, false, block);
		CastInst *cinst = new BitCastInst(ptr_aux, PointerType::get(IntegerType::get(global_context, 8), 0), "bitcast", block);
		args.push_back(cinst);

		ArrayRef<Value*> argsRef(args);
		return CallInst::Create(print, argsRef, "", block);
	}

