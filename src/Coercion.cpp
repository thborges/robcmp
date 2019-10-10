#include "Header.h"
	
Value *Coercion::Convert(Value *v, Type *destty, BasicBlock *block, bool unsig){

	Value *r = v;
	Type *ty = v->getType();

	if (ty != destty){
		//Float to Integer
		if ((ty->isFloatTy() || destty->isDoubleTy()) && destty -> isIntegerTy()){
			r = new FPToSIInst(v, destty, "", block);
		}
		//Integer to Float
		else if ((destty->isFloatTy() || destty->isDoubleTy())&& ty->isIntegerTy()){
			r = new SIToFPInst(v, destty, "", block);
		}
		//Float/Double to Float/Double
		
		if ((ty->isFloatTy() || destty->isDoubleTy()) && (destty -> isFloatTy() || destty -> isDoubleTy())){
			r = new FPExtInst(v, destty, "", block);
		}
		//Generic ExtInt to Int
		else if (destty->isIntegerTy() && ty->isIntegerTy()){
			unsigned wty = dyn_cast<IntegerType>(ty)->getBitWidth();
			unsigned wdestty = dyn_cast<IntegerType>(destty)->getBitWidth();
			if (wty > wdestty){
				r = new TruncInst(v, destty, "", block);
			}
			else if (wty < wdestty){
				r = new SExtInst(v, destty, "", block);
			}
//			else if (ty != destty)//To solve bug (TEMPORARY)
//				r = new SExtInst(v, destty);
		}
	}
	return r;

}
