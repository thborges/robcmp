#include "Header.h"

LanguageDataType Load::getResultType(BasicBlock *block, BasicBlock *allocblock) {
	auto rsym = search_symbol(ident, allocblock, block);
	if (rsym) {
		if (complexIdent) {
			auto it = rsym->structure->fields.find(complexIdent->names[1]);
			if (it != rsym->structure->fields.end()) {
				return it->second.fieldDataType;
			}
		} else
			return rsym->dt;
	}
	return tvoid;
}

Value* Load::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {
	auto rsym = search_symbol(ident, allocblock, block);
	if (rsym == NULL) {
		yyerrorcpp("Variable " + ident + " not defined.", this);
		return NULL;
	}
	Field field;

	// semantic validation of complexIdent
	if (complexIdent) {
		string idfield = complexIdent->names[1];
		auto fieldit = rsym->structure->fields.find(idfield);
		if (fieldit == rsym->structure->fields.end()) {
			yyerrorcpp("Field " + idfield + " not declared in " + ident, this);
			return NULL;
		} else {
			field = fieldit->second;
		}
	}

	auto sym = rsym->value;
	if (rsym->qualifier == qconst)
		return sym;

	if (block == NULL && (allocblock == NULL || allocblock == global_alloc)) {
		// trying to load a variable to initialize a global one.
		// permitted only for const globals
		if (rsym->qualifier != qconst) {
			yyerrorcpp("Can't not use '" + ident + "' to define another var/const in global context.", this);
			return NULL;
		}
	}
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);

	bool vol = rsym->qualifier == qvolatile;
	Type *ty = robTollvmDataType[rsym->dt];
	Value *v = Builder->CreateLoad(ty, sym, vol, ident);

	if (complexIdent) {
		/* this code does:
		 *   v = symbol->value << pointerbits - field_start - field_width
		 *   v = v >> pointer_bits - field_width
		 */
		int bs = LanguageDataTypeBitWidth[rsym->dt] - field.bitWidth;
		if (bs - field.startBit > 0)
			v = Builder->CreateShl(v, ConstantInt::get(ty, bs - field.startBit));
		if (bs > 0)
			v = Builder->CreateAShr(v, ConstantInt::get(ty, bs));
		v = Builder->CreateTrunc(v, robTollvmDataType[field.fieldDataType]);
	}

	return v;
}

void Load::accept(Visitor &v) {
	v.visit(*this); 
}

bool Load::isConstExpr(BasicBlock *block, BasicBlock *allocblock) {
	RobSymbol *rsym = search_symbol(ident, block, allocblock);
	return rsym && (dyn_cast<Constant>(rsym->value) != NULL);
}
