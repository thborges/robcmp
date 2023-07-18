#include "Header.h"

void DebugInfo::emitLocation(SourceLocation *s) {
	if (!s)
		return Builder->SetCurrentDebugLocation(DebugLoc());
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
	return files.back();
}

DIScope* DebugInfo::currScope() {
	return scopes.back();
}

