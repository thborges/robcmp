#include "Header.h"

Scalar::Scalar(const char *n, Node *e, DataQualifier qualifier) : 
	name(n), expr(e), qualifier(qualifier), complexIdent(nullptr) {
	node_children.reserve(1);
	node_children.push_back(e);
}

Scalar::Scalar(ComplexIdentifier *ci, Node *e, DataQualifier qualifier) : 
	complexIdent(ci), expr(e), qualifier(qualifier) {
	node_children.reserve(1);
	node_children.push_back(e);
}

Value *Scalar::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

	string id = complexIdent ? complexIdent->names[0] : name;
	auto symbol = search_symbol(id, allocblock, block);
	Field field;

	if (complexIdent) {
		string idfield = complexIdent->names[1];
		auto fieldit = symbol->structure->fields.find(idfield);

		if (symbol == NULL) {
			yyerrorcpp("Symbol " + id + " must be defined first.", this);
			return NULL;
		} else if (fieldit == symbol->structure->fields.end()) {
			yyerrorcpp("Symbol " + id + "." + idfield + " not declared.", this);
			return NULL;
		} else {
			field = fieldit->second;
		}
	}

	// variable doesn't exists
	if (symbol == NULL) {
		Value *ret, *leftv;
		Value *exprv = expr->generate(func, block, allocblock);
		if (!exprv)
			return NULL;
		
		if (allocblock == global_alloc) {
			Constant *exprvc = dyn_cast<Constant>(exprv);
			if (exprvc == NULL)
				return NULL; //TODO: semantic error, global const value can't be generated

			if (qualifier == qconst)
				ret = leftv = exprvc;
			else {
				GlobalVariable *gv = new GlobalVariable(*mainmodule, exprvc->getType(), 
					false, GlobalValue::CommonLinkage, exprvc, name);
				ret = leftv = gv;
			}
		} else {
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
			ret = new StoreInst(exprv, leftv, qualifier == qvolatile, block);
		}

		tabelasym[allocblock][name] = new RobSymbol(leftv, qualifier);
		return ret;

	} else {
		// variable already exists
		if (symbol->qualifier == qconst) {
			yyerrorcpp("Constant '" + name + "' can not be changed.", this);
			return NULL;
		}

		Type *leftvty = symbol->value->getType();
		qualifier = symbol->qualifier;
		if (symbol->pointerType)
			leftvty = symbol->pointerType;
		Value *exprv = expr->generate(func, block, allocblock);
		Value *nvalue;

		if (complexIdent) {
			/* this code does:
			 *   symbol->value &= ~(0x11... << field.startBit)
			 *   symbol->value |= (exprv << field.startBit)
			 */

			// Coerce the left side to the field size
			exprv = Coercion::Convert(exprv, robTollvmDataType[field.fieldDataType], block, expr);
			// Expand to the left side size
			exprv = Coercion::Convert(exprv, leftvty, block, expr);
			
			// Prepare the mask
			Constant *allone = Constant::getAllOnesValue(Type::getIntNTy(global_context, field.bitWidth));
			Constant *ones = ConstantExpr::getZExt(allone, leftvty);

			if (field.startBit > 0) {
				Constant *shiftl = ConstantInt::get(leftvty, field.startBit);
				ones = ConstantExpr::getShl(ones, shiftl);
				exprv = BinaryOperator::CreateShl(exprv, shiftl, "shift", block);
			}
			Constant *mask = ConstantExpr::getNot(ones);

			// Load pointer value
			Load ld(id);
			Value *leftv = ld.generate(func, block, allocblock);

			// Apply mask, than or
			Value *vaftermask = BinaryOperator::CreateAnd(leftv, mask, "mask", block);
			nvalue = BinaryOperator::CreateOr(vaftermask, exprv, "setbits", block);
		} else {
			nvalue = Coercion::Convert(exprv, leftvty, block, expr);
		}

		return new StoreInst(nvalue, symbol->value, qualifier == qvolatile, block);
	}
}

void Scalar::accept(Visitor& v) {
	v.visit(*this);
}
