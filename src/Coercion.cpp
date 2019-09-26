#include "Header.h"
	
Value *Coercion::Convert(Value *v, Type *destty, bool unsig){

	Value *r = v;
	Type *ty = v->getType();

	if (ty != destty){
		//Float to Integer
		if ((ty->isFloatTy() || destty->isDoubleTy()) && destty -> isIntegerTy()){
			r = new FPToSIInst(v, destty);
		}
		//Integer to Float
		else if ((destty->isFloatTy() || destty->isDoubleTy())&& ty->isIntegerTy()){
			r = new SIToFPInst(v, destty);
		}
		//Float/Double to Float/Double
		
		if ((ty->isFloatTy() || destty->isDoubleTy()) && (destty -> isFloatTy() || destty -> isDoubleTy())){
			r = new FPExtInst(v, destty);
		}
		//Generic ExtInt to Int
		else if (destty->isIntegerTy() && ty->isIntegerTy()){
			unsigned wty = dyn_cast<IntegerType>(ty)->getBitWidth();
			unsigned wdestty = dyn_cast<IntegerType>(ty)->getBitWidth();
			if (wty > wdestty){
				r = new TruncInst(v, destty);
			}
			else if (wty < wdestty){
				r = new SExtInst(v, destty);
			}
			else if (ty != destty)//To solve bug (TEMPORARY)
				r = new SExtInst(v, destty);
		}
	}
	return r;

}
