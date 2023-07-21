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

Value *Coercion::Convert(Value *v, Type *destty, BasicBlock *block, SourceLocation *loc, bool isCast){

	Value *r = v;
	Type *ty = v->getType();

	RobDbgInfo.emitLocation(loc);
	Builder->SetInsertPoint(block);
	
	if (ty != destty){
		//Float to Integer
		if (ty->isFloatingPointTy() && destty->isIntegerTy()){
			if (Constant *c = dyn_cast<Constant>(v))
				r = ConstantExpr::getFPToSI(c, destty);
			else
				r = Builder->CreateFPToSI(v, destty, "fptosi");
			if (!isCast)
				yywarncpp("Float point converted to integer.", loc);
		}
		//Integer to Float
		else if (destty->isFloatingPointTy() && ty->isIntegerTy()){
			if (Constant *c = dyn_cast<Constant>(v))
				r = ConstantExpr::getSIToFP(c, destty);
			else
				r = Builder->CreateSIToFP(v, destty, "sitofp");
		}
		//Floating point to Floating point
		else if (ty->isFloatingPointTy() && destty->isFloatingPointTy()) {
			unsigned tybw = GetFloatingPointBitwidth(ty);
			unsigned dtybw = GetFloatingPointBitwidth(destty);
			if (dtybw > tybw)
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getFPExtend(c, destty);
				else
					r = Builder->CreateFPExt(v, destty, "fpext");
			else if (dtybw < tybw) {
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getFPTrunc(c, destty);
				else
					r = Builder->CreateFPTrunc(v, destty, "fptrunc");
				if (!isCast)
					yywarncpp("Float point value truncated.", loc);
			}
		}
		//Generic ExtInt to Int
		else if (destty->isIntegerTy() && ty->isIntegerTy()){
			unsigned wty = ty->getIntegerBitWidth();
			unsigned wdestty = destty->getIntegerBitWidth();
			if (wty > wdestty){
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getTrunc(c, destty);
				else
					r = Builder->CreateTrunc(v, destty, "trunc");
				if (!isCast)
					yywarncpp("Integer value truncated.", loc);
			}
			else if (wty < wdestty) {
				if (Constant *c = dyn_cast<Constant>(v))
					r = ConstantExpr::getSExt(c, destty);
				else
					r = Builder->CreateSExt(v, destty, "sext");
			}
		}
		else if (!destty->isPointerTy()) {
			yyerrorcpp("No coercion between " + getTypeName(ty) + " and " + 
				getTypeName(destty) + " implemented.", loc);
		}
	}
	return r;

}
