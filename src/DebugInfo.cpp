#include "HeaderGlobals.h"
#include "SourceLocation.h"
#include "Node.h"

void DebugInfo::emitLocation(SourceLocation *s) {
	if (!debug_info)
		return;
	if (!s)
		return Builder->SetCurrentDebugLocation(DebugLoc());
	if (s->getLineNo() == 0)
		return;
	
	DIScope *scope;
	if (scopes.empty())
		scope = cunit;
	else
		scope = scopes.back();
	
	Builder->SetCurrentDebugLocation(DILocation::get(
		scope->getContext(), s->getLineNo(), s->getColNo(), scope));
}

void DebugInfo::push_scope(DIFile *f, DIScope *s) {
	scopes.push_back(s);
	files.push_back(f);
}

void DebugInfo::pop_scope() {
	scopes.pop_back();
	files.pop_back();
}

DIFile* DebugInfo::currFile() {
	if (!debug_info)
		return NULL;
	return files.back();
}

DIScope* DebugInfo::currScope() {
	if (!debug_info)
		return NULL;
	return scopes.back();
}

void DebugInfo::declareVar(Node *n, Value *alloc, BasicBlock *allocblock) {
	DataType dt = n->getDataType();
	llvm::DIType *dty = buildTypes->diType(dt);
	if (n->hasQualifier(qvolatile)) {
		dty = DBuilder->createQualifiedType(dwarf::DW_TAG_volatile_type, dty);
	}
	auto sp = RobDbgInfo.currScope();
	auto funit = RobDbgInfo.currFile();
	DILocalVariable *d = DBuilder->createAutoVariable(
		sp, n->getName(), funit, n->getLineNo(), dty, true);
	DBuilder->insertDeclare(alloc, d, DBuilder->createExpression(),
		DILocation::get(sp->getContext(), n->getLineNo(), n->getColNo(), sp), allocblock);
}
