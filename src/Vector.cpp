#include "Header.h"

	Value *Vector::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
		// generate code to produce the new variable value
		Value *exprv = expr->generate(func, block, allocblock);

		//Value *leftv = search_symbol(name, allocblock, block);
		/* if (leftv == NULL) {
			if (allocblock == global_alloc) {
				GlobalVariable *gv = new GlobalVariable(*mainmodule, exprv->getType(), 
					false, GlobalValue::CommonLinkage, NULL, name);
				if (exprv->getType()->isIntegerTy())
					gv->setInitializer(ConstantInt::get(exprv->getType(), 0));
				else if (exprv->getType()->isFloatTy())
					gv->setInitializer(ConstantFP::get(exprv->getType(), 0.0));
				else
					yyerrorcpp("Global variable default initialization not defined.");

				leftv = gv;
			} else {
				leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
			}
			tabelasym[allocblock][name] = leftv; 
		}

		auto nvalue = exprv;
		if (leftv->getType()->getPointerElementType()->isIntegerTy() && 
			exprv->getType()->isFloatTy()) {
			nvalue = new FPToSIInst(exprv, leftv->getType()->getPointerElementType(), 
				"truncistore", block);
		}
		StoreInst *ret = new StoreInst(nvalue, leftv, false, block);
		return ret;
		*/

		Type* I = exprv->getType();
		//Type* I = IntegerType::getInt32Ty(getContext());
		auto num = 10;
		ArrayType* arrayType = ArrayType::get(I, num);

		AllocaInst* variable = new AllocaInst(arrayType, 0, name, allocblock);


		//auto load = new LoadInst(variable, "loader", block);

		//Value* arr_alloc = new AllocaInst(I, 0, "my_array", allocblock);	
		// Add to table of symbols
		StoreInst *ret = new StoreInst(ConstantInt::get(arrayType, APInt(32, 10)), variable, allocblock);
		//tabelasym[allocblock][name] = variable;
		return ret;
	//	StoreInst *ret = new StoreInst (10, arr_alloc, false, block);
	//	return ret;
	}
