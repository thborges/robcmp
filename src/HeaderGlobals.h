
#pragma once

#include "HeaderExternals.h"

// Program main module and IR Builder
extern Module* mainmodule;
extern BasicBlock* global_alloc;
extern LLVMContext global_context;
extern unique_ptr<IRBuilder<>> Builder;

class BuildTypes;
extern unique_ptr<BuildTypes> buildTypes;

class SourceLocation;
class Node;

// Debug Info
extern bool debug_info;
extern unique_ptr<DIBuilder> DBuilder;
struct DebugInfo {
	DICompileUnit *cunit;
	vector<DIFile *> files;
	vector<DIScope *> scopes;
	void emitLocation(SourceLocation *s);
	void push_scope(DIScope*);
	void push_file(DIFile*);
	void pop_scope();
	void pop_file();
	DIFile *currFile();
	DIScope *currScope();
	void declareVar(Node *n, Value *alloc, BasicBlock *allocblock);
	DIExpression *getFixedOffsetExpression();
};
extern struct DebugInfo RobDbgInfo;

// Error messages
void yyerrorcpp(const string& s, SourceLocation *n, bool semantic = true);
void yywarncpp(const string& s, SourceLocation *n);

template<typename ... Args>
string string_format(const char *format, Args ... args) {
    int size_s = snprintf(nullptr, 0, format, args ...) + 1;
    if( size_s <= 0 ) { 
		return "";
	}
    auto size = static_cast<size_t>(size_s);
    unique_ptr<char[]> buf(new char[ size ]);
    snprintf(buf.get(), size, format, args ...);
    return string(buf.get(), buf.get() + size - 1);
}

class Node;
