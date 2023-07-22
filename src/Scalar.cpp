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

	RobDbgInfo.emitLocation(this);

	string id = complexIdent ? complexIdent->names[0] : name;
	auto symbol = search_symbol(id, allocblock, block);
	Field field;

	// semantic validation of complexIdent
	if (complexIdent) {
		string idfield = complexIdent->names[1];
		auto fieldit = symbol->structure->fields.find(idfield);

		if (symbol == NULL) {
			yyerrorcpp("Symbol " + id + " must be defined first.", this);
			return NULL;
		} else if (fieldit == symbol->structure->fields.end()) {
			yyerrorcpp("Field " + idfield + " not declared in " + id, this);
			return NULL;
		} else {
			field = fieldit->second;
		}
	}

	// variable doesn't exists
	if (symbol == NULL) {
		Value *ret, *leftv;
		Value *exprv = expr->generate(func, block, allocblock);
		BasicDataType dt = expr->getResultType(block, allocblock);

		if (!exprv)
			return NULL;
		
		auto sp = RobDbgInfo.currScope();
		auto funit = RobDbgInfo.currFile();

		if (allocblock == global_alloc) {
			Constant *exprvc = dyn_cast<Constant>(exprv);
			if (exprvc == NULL)
				return NULL; //TODO: semantic error, global const value can't be generated

			if (qualifier == qconst)
				ret = leftv = exprvc;
			else {
				GlobalVariable *gv = new GlobalVariable(*mainmodule, buildTypes->llvmType(dt),
					false, GlobalValue::CommonLinkage, exprvc, name);
				ret = leftv = gv;

				if (debug_info) {
					auto *d = DBuilder->createGlobalVariableExpression(sp, name, "",
						funit, getLineNo(), buildTypes->diType(dt), false);
					gv->addDebugInfo(d);
				}
			}
		} else {
			Builder->SetInsertPoint(allocblock);
			AllocaInst *newvar = Builder->CreateAlloca(exprv->getType(), 0, name);
			newvar->setAlignment(Align(1));
			leftv = newvar;
			Builder->SetInsertPoint(block);
			ret = Builder->CreateStore(exprv, leftv, qualifier == qvolatile);
			
			if (debug_info) {
				llvm::DIType *dty = buildTypes->diType(dt);
				if (qualifier == qvolatile) {
					dty = DBuilder->createQualifiedType(dwarf::DW_TAG_volatile_type, dty);
				}
				DILocalVariable *d = DBuilder->createAutoVariable(
					sp, name, funit, getLineNo(), dty, true);
				DBuilder->insertDeclare(leftv, d, DBuilder->createExpression(),
					DILocation::get(sp->getContext(), getLineNo(), getColNo(), sp), allocblock);
			}
		}

		RobSymbol *rs = new RobSymbol(leftv, qualifier);
		rs->dt = dt;
		tabelasym[allocblock][name] = rs;
		return ret;

	} else {
		// variable already exists
		if (symbol->qualifier == qconst) {
			yyerrorcpp("Constant '" + name + "' can not be changed.", this);
			return NULL;
		}

		Type *leftvty = buildTypes->llvmType(symbol->dt);
		qualifier = symbol->qualifier;
		Value *exprv = expr->generate(func, block, allocblock);
		Value *nvalue;

		Builder->SetInsertPoint(block);

		if (complexIdent) {
			/* this code does:
			 *   symbol->value &= ~(0x11... << field.startBit)
			 *   symbol->value |= (exprv << field.startBit)
			 */

			// Coerce the left side to the field size
			exprv = Coercion::Convert(exprv, buildTypes->llvmType(field.fieldDataType), block, expr);
			// Expand to the left side size
			exprv = Coercion::Convert(exprv, leftvty, block, expr);
			
			// Prepare the mask
			Constant *allone = Constant::getAllOnesValue(Type::getIntNTy(global_context, field.bitWidth));
			Constant *ones = ConstantExpr::getZExt(allone, leftvty);

			if (field.startBit > 0) {
				Constant *shiftl = ConstantInt::get(leftvty, field.startBit);
				ones = ConstantExpr::getShl(ones, shiftl);
				exprv = Builder->CreateShl(exprv, shiftl, "shift");
			}
			Constant *mask = ConstantExpr::getNot(ones);

			// Load pointer value
			Load ld(id);
			ld.setLocation(expr);
			Value *leftv = ld.generate(func, block, allocblock);

			// Apply mask, than or
			Builder->SetInsertPoint(block); //caution, after generate!
			Value *vaftermask = Builder->CreateAnd(leftv, mask, "mask");
			nvalue = Builder->CreateOr(vaftermask, exprv, "setbits");
		} else {
			nvalue = Coercion::Convert(exprv, leftvty, block, expr);
		}

		return Builder->CreateStore(nvalue, symbol->value, qualifier == qvolatile);
	}
}

void Scalar::accept(Visitor& v) {
	v.visit(*this);
}
