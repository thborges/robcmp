
#include "Load.h"
#include "BuildTypes.h"
#include "FunctionImpl.h"
#include "Variable.h"
#include "Pointer.h"

Node* Load::getIdentSymbol(bool showError) {
	if (!identSymbol) {
		identSymbol = ident.getSymbol(getScope(), false);
	}
	if (!identSymbol && showError)
        yyerrorcpp("Symbol " + ident.getFullName() + " not found.", this);
	return identSymbol;
}

DataType Load::getDataType() {
	if (dt == BuildTypes::undefinedType) {
		if (getIdentSymbol())
			dt = identSymbol->getDataType();
	}
	return dt;
}

Value* Load::generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) {

	if (!identSymbol) {
		identSymbol = ident.getSymbol(getScope(), false);
		if (!identSymbol) {
			identSymbol = ident.getSymbol(func, false);
			//assert(false && "when this is executed?");//FIXME
		}
	}
	
	if (identSymbol && identSymbol->isConstExpr())
		return identSymbol->getLLVMValue(func);
	
	Variable *symbol = dynamic_cast<Variable*>(identSymbol);
	if (!symbol) {
        yyerrorcpp("Symbol " + ident.getFullName() + " not found.", this);
		return NULL;
	}

	dt = identSymbol->getDataType();

	if (block == NULL && (allocblock == NULL || allocblock == global_alloc)) {
		// trying to load a variable to initialize a global one.
		// permitted only for const globals
		if (!symbol->hasQualifier(qconst)) {
			yyerrorcpp("Can not use '" + ident.getFullName() + "' to define another var/const in global context.", this);
			return NULL;
		}
	}
	
	RobDbgInfo.emitLocation(this);
	Builder->SetInsertPoint(block);
	
	Value *alloc = NULL;
	if (ident.isComplex()) {
		Identifier istem = ident.getStem();
		Node *stem = istem.getSymbol(getScope());

		// Pointers need a custom procedure: load the stem and get the 
		// requested bit value through bit shifting
		Pointer *reg = dynamic_cast<Pointer*>(stem);
		if (reg && buildTypes->isComplex(reg->getDataType())) {
			alloc = reg->getLLVMValue(NULL);
			Type *req_eq_ty = Type::getIntNTy(global_context, buildTypes->bitWidth(reg->getDataType()));
			Value *v = Builder->CreateLoad(req_eq_ty, alloc, reg->hasQualifier(qvolatile), "ptrvalue");
			/* this code does:
			 *   v = symbol->value << pointerbits - field_start - field_width
			 *   v = v >> pointer_bits - field_width
			 */
			int bs = buildTypes->bitWidth(reg->getDataType()) - buildTypes->bitWidth(symbol->getDataType());
			unsigned fieldStartBit = reg->getFieldStartBit(symbol);
			if (bs - fieldStartBit > 0)
				v = Builder->CreateShl(v, ConstantInt::get(req_eq_ty, bs - fieldStartBit));
			if (bs > 0)
				v = Builder->CreateLShr(v, ConstantInt::get(req_eq_ty, bs));
			return Builder->CreateTrunc(v, buildTypes->llvmType(symbol->getDataType()));
		} else if (symbol->isPseudoVar()) {
			alloc = symbol->getLLVMValue(stem, func);
		} else {
			// not pointer and isComplex: two or more recursive levels: a.x.y
			alloc = getRecursiveField(ident, getScope(), func);
		}
		
		if (stem->hasQualifier(qvolatile))
			symbol->setQualifier(qvolatile);

		// when the new var will be a reference to expr;
		// we change its scope to the scope of expr (stem)
		// this is needed by injection
		if (leftValue)
			leftValue->setScope(stem, true);
	} else {
		alloc = symbol->getLLVMValue(func);
	}

	if (!alloc) {
		yyerrorcpp(string_format("Symbol %s is undefined at this point.", ident.getFullName().c_str()), this);
		return NULL; // Caused by an error on previous statement that defines the symbol
	}

	DataType sdt = symbol->getDataType();
	if (buildTypes->isComplex(sdt) || buildTypes->isArrayOrMatrix(sdt)) {
		if (symbol->isPointerToPointer()) {
			Type *ty = PointerType::getUnqual(buildTypes->llvmType(sdt));
			alloc = Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), "deref");
		}
		if (leftValue)
			leftValue->setPointerToPointer(true);
		return alloc;
	} else {
		Type *ty = buildTypes->llvmType(sdt);
		return Builder->CreateLoad(ty, alloc, symbol->hasQualifier(qvolatile), ident.getFullName());
	}
}

bool Load::isConstExpr() {
	Node *symbol = ident.getSymbol(getScope());
	return symbol && symbol->isConstExpr();
}

void Load::setLeftValue(Variable *symbol) {
    leftValue = symbol;
}

Value* Load::getRecursiveField(Identifier &ident, Node *scope, FunctionImpl *func) {
	list<Node*> symbols;
	Node *last = ident.getSymbol(scope, false, &symbols);
	symbols.push_back(last);
	
	Node *first = symbols.front();
	symbols.pop_front();
	Value *alloc = first->getLLVMValue(func);
	assert(alloc && "Can't get a field of an unallocated symbol.");

	Type *udt = buildTypes->llvmType(first->getDataType());
	if (first->isPointerToPointer()) {
		alloc = Builder->CreateLoad(PointerType::getUnqual(udt), alloc, "deref");
	}

	for(auto &x : symbols) {
		Variable *var = dynamic_cast<Variable*>(x);
		if (var) {
			int gepidx = var->getGEPIndex();
			if (var->isPointerToPointer()) {
				alloc = Builder->CreateLoad(PointerType::getUnqual(udt), alloc, "deref");
			}
			alloc = Builder->CreateStructGEP(udt, alloc, gepidx, x->getName());		
			udt = buildTypes->llvmType(var->getDataType());
		} else {
			yyerrorcpp(x->getName() + " is not a variable.", &ident);
			break;
		}
	}
	return alloc;
}