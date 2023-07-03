#include "Header.h"

Scalar::Scalar(const char *n, Node *e, DataQualifier qualifier) : 
	name(n), expr(e), qualifier(qualifier) {
	node_children.reserve(1);
	node_children.push_back(e);
}

Constant *Scalar::tryToGenerateAsConstant(Node *n) {
	vector<Node *> nchildren = n->children();
	if (nchildren.size() > 0) {
		Constant *children[nchildren.size()];
		for (int i = 0; i < nchildren.size(); i++) {
			children[i] = tryToGenerateAsConstant(nchildren[i]);
			if (children[i] == NULL)
				return NULL;
		}
		if (BinaryOp *bo = dynamic_cast<BinaryOp*>(n)) {
			Constant *c0 = children[0];
			Constant *c1 = children[1];
			Type *ty0 = c0->getType();
			Type *ty1 = c1->getType();
			if (ty0->isIntegerTy() && ty1->isIntegerTy()) {
				unsigned b0 = dyn_cast<IntegerType>(ty0)->getBitWidth();
				unsigned b1 = dyn_cast<IntegerType>(ty1)->getBitWidth();
				if (b0 > b1)
					c1 = ConstantExpr::getSExt(c1, ty0);
				else if (b1 > b0)
					c0 = ConstantExpr::getSExt(c0, ty1);
			} else {
				assert("FIXME! Implement coercion between distinct constant types.");
			}

			switch (bo->getOperator()) {
				case '+': return ConstantExpr::getAdd(c0, c1);
				case '-': return ConstantExpr::getSub(c0, c1);
				case '*': return ConstantExpr::getMul(c0, c1);
				
				case TOK_OR:
				case '|': return ConstantExpr::getOr(c0, c1);
				
				case TOK_AND:
				case '&': return ConstantExpr::getAnd(c0, c1);

				case '^': return ConstantExpr::getXor(c0, c1);
				case TOK_LSHIFT: return ConstantExpr::getShl(c0, c1);
				case TOK_RSHIFT: return ConstantExpr::getLShr(c0, c1);
				default:
					return NULL;
			}
		} else if (dynamic_cast<FlipOp*>(n)) {
			return ConstantExpr::getNeg(children[0]);
		} else
			return NULL;
			
	} else {
		Value *v = NULL;
		if (dynamic_cast<Int1*>(n) ||
			dynamic_cast<Int8*>(n) ||
			dynamic_cast<Int16*>(n) ||
			dynamic_cast<Int32*>(n) ||
			dynamic_cast<Int64*>(n) ||
			dynamic_cast<Half*>(n) ||
			dynamic_cast<Float*>(n) ||
			dynamic_cast<Double*>(n) ||
			dynamic_cast<Float128*>(n) ||
			dynamic_cast<Load*>(n)) // Load can return constants in the global context
			v = n->constGenerate();
		
		if (v == NULL)
			return NULL;
		else
			return dyn_cast<Constant>(v);
	}
}

Value *Scalar::generate(Function *func, BasicBlock *block, BasicBlock *allocblock) {

	auto symbol = search_symbol(name, allocblock, block);

	// variable doesn't exists
	if (symbol == NULL) {
		Value *ret, *leftv;

		if (allocblock == global_alloc) {
			Constant *exprv = tryToGenerateAsConstant(expr);
			if (exprv == NULL)
				return NULL;

			if (qualifier == qconst)
				ret = leftv = exprv;
			else {
				GlobalVariable *gv = new GlobalVariable(*mainmodule, exprv->getType(), 
					false, GlobalValue::CommonLinkage, exprv, name);
				ret = leftv = gv;
			}
		} else {
			Value *exprv = expr->generate(func, block, allocblock);
			if (!exprv)
				return NULL;
			leftv = new AllocaInst(exprv->getType(), 0, name, allocblock);
			ret = new StoreInst(exprv, leftv, qualifier == qvolatile, block);
		}

		tabelasym[allocblock][name] = new RobSymbol(leftv, qualifier);
		return ret;

	} else {
		if (symbol->qualifier == qconst) {
			yyerrorcpp("Constant '" + name + "' can not be changed.", this);
			return NULL;
		}
		// variable already exists
		Type *leftvty = symbol->value->getType();
		qualifier = symbol->qualifier;
		if (symbol->pointerType)
			leftvty = symbol->pointerType;
		Value *exprv = expr->generate(func, block, allocblock);
		auto nvalue = Coercion::Convert(exprv, leftvty, block);
		return new StoreInst(nvalue, symbol->value, qualifier == qvolatile, block);
	}
}

void Scalar::accept(Visitor& v) {
	v.visit(*this);
}
