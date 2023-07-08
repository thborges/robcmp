#ifndef __COERCION_H__
#define __COERCION_H__

class Coercion{
	public:
		static Value *Convert(Value *v, Type *destty, BasicBlock *block, SourceLocation *loc);
		static unsigned GetFloatingPointBitwidth(Type *ty);
};

#endif
