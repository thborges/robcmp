
#pragma once

#include "HeaderExternals.h"
#include "SourceLocation.h"

class Coercion{
public:
	static Value *Convert(Value *v, Type *destty, BasicBlock *block, SourceLocation *loc,
		bool isCast = false);
	static unsigned GetFloatingPointBitwidth(Type *ty);
};
