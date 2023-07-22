#include "Header.h"

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

