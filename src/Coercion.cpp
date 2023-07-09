#include "Header.h"

unsigned Coercion::GetFloatingPointBitwidth(Type *ty) {
	switch (ty->getTypeID()) {
		case Type::FloatTyID:
			return 32;
		case Type::DoubleTyID:
			return 64;
		case Type::X86_FP80TyID:
			return 80;
		case Type::PPC_FP128TyID:
		case Type::FP128TyID:
			return 128;
		default:
			return 0;
	}
}

Value *Coercion::Convert(Value *v, Type *destty, BasicBlock *block, SourceLocation *loc){

	Value *r = v;
	Type *ty = v->getType();
	
	if (ty != destty){
		//Float to Integer
		if (ty->isFloatingPointTy() && destty->isIntegerTy()){
			if (Constant *c = dyn_cast<Constant>(v))
				r = ConstantExpr::getFPToSI(c, destty);
			else
				r = new FPToSIInst(v, destty, "fptosi", block);
			yywarncpp("Float point converted to integer.", loc);
		}
		//Integer to Float
		else if (destty->isFloatingPointTy() && ty->isIntegerTy()){
			if (Constant *c = dyn_cast<Constant>(v))
				r = ConstantExpr::getSIToFP(c, destty);
			else
				r = new SIToFPInst(v, destty, "sitofp", block);
		}
		//Floating point to Floating point
		else if (ty->isFloatingPointTy() && destty->isFloatingPointTy()) {
			unsigned tybw = GetFloatingPointBitwidth(ty);
			unsigned dtybw = GetFloatingPointBitwidth(destty);
			if (dtybw > tybw)
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getFPExtend(c, destty);
				else
					r = new FPExtInst(v, destty, "fpext", block);
			else if (dtybw < tybw) {
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getFPTrunc(c, destty);
				else
					r = new FPTruncInst(v, destty, "fptrunc", block);
				yywarncpp("Float point value truncated.", loc);
			}
		}
		//Generic ExtInt to Int
		else if (destty->isIntegerTy() && ty->isIntegerTy()){
			unsigned wty = dyn_cast<IntegerType>(ty)->getBitWidth();
			unsigned wdestty = dyn_cast<IntegerType>(destty)->getBitWidth();
			if (wty > wdestty){
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getTrunc(c, destty);
				else
					r = new TruncInst(v, destty, "trunc", block);
				yywarncpp("Integer value truncated.", loc);
			}
			else if (wty < wdestty) {
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getSExt(c, destty);
				else
					r = new SExtInst(v, destty, "sext", block);
			}
		}
		else if (!destty->isPointerTy()) {
			yyerrorcpp("No coercion between " + getTypeName(ty) + " and " + 
				getTypeName(destty) + " implemented.", loc);
		}
	}
	return r;

}
