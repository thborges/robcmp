#ifndef __HEADER_H__
#define __HEADER_H__

//#define ENABLE_ARDUINO
//#define ENABLE_PRINT
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/ADT/StringExtras.h>

using namespace std;
using namespace llvm;

/* After adding new types here, go to Program::generate to fill
 * the robTollvmDataType vector */
enum LanguageDataType {tvoid, tbool, tchar, tint8, tint16, tint32, tint64, 
  tint8u, tint16u, tint32u, tint64u, tfloat, tdouble, tldouble,
  __ldt_last};

static bool isIntegerDataType(LanguageDataType dt) {
	return dt >= tint8 && dt <= tint64u;
}

static bool isFloatDataType(LanguageDataType dt) {
	return dt >= tfloat && dt <= tldouble;
}

static const char *LanguageDataTypeNames[__ldt_last] = {"void", "boolean", "char", "int8",
	"int16", "int32", "int64", "unsigned int8", "unsigned int16",
	"unsigned int32", "unsigned int64", "float",
	"double", "long double"};

static const unsigned LanguageDataTypeBitWidth[__ldt_last] = {0, 1, 8, 8,
	16, 32, 64, 8, 16, 32, 64, 32, 64, 128};

static const unsigned LanguageDataTypeDwarfEnc[__ldt_last] = {
	dwarf::DW_ATE_address, 
	dwarf::DW_ATE_boolean,
	dwarf::DW_ATE_unsigned_char,
	dwarf::DW_ATE_signed, dwarf::DW_ATE_signed, dwarf::DW_ATE_signed, dwarf::DW_ATE_signed,
	dwarf::DW_ATE_unsigned, dwarf::DW_ATE_unsigned, dwarf::DW_ATE_unsigned, dwarf::DW_ATE_unsigned,
	dwarf::DW_ATE_float, dwarf::DW_ATE_float, dwarf::DW_ATE_float
};

enum DataQualifier {qnone, qconst, qvolatile};

extern Type* robTollvmDataType[];

class Node;
class Stmts;
class ArrayElements;
class MatrixElements;
class FunctionParams;
class ParamsCall;

typedef struct {
	Node *value;
	unsigned count;
} ArrayElement;

typedef struct {
	const char *name;
	LanguageDataType type;
} FunctionParam;

typedef struct {
	ArrayElements *array;
	unsigned count;
} MatrixElement;

#include "Field.h"

typedef struct {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} location_t;

#include "bison.hpp"

extern int yyerror(const char *s);
extern int yylex();
extern Node* getNodeForIntConst(int64_t i);

extern char* build_filename;
extern char* build_outputfilename;

#include "SourceLocation.h"

// Program main module and IR Builder
extern Module* mainmodule;
extern BasicBlock* global_alloc;
extern LLVMContext global_context;
extern std::unique_ptr<IRBuilder<>> Builder;

// Debug Info
extern bool debug_info;
extern std::unique_ptr<DIBuilder> DBuilder;
struct DebugInfo {
	DICompileUnit *cunit;
	DIType *types[__ldt_last];
	vector<DIFile *> files;
	vector<DIScope *> scopes;
	void emitLocation(SourceLocation *s);
	void push_scope(DIFile *f, DIScope *);
	void pop_scope();
	DIFile *currFile();
	DIScope *currScope();
};
extern struct DebugInfo RobDbgInfo;

// symbol table
#include "RobSymbol.h"
extern map<BasicBlock*, map<string, RobSymbol*>> tabelasym;

// arduino functions
extern Function *analogWrite;
extern Function *analogRead;
extern Function *delay;
extern Function *delayMicroseconds;
extern Function *init;
extern Function *print;
extern Function *i16div;

typedef struct {
	const char *name;
	const char *triple;
	const char *cpu;
	const char *features;
} TargetInfo;

static TargetInfo supportedTargets[] = {
	{"", "", "", ""}, // default target
	{"avr328p", "avr-atmel-none", "atmega328p", "+avr5"},
	{"stm32f1", "thumbv7m-none-eabi", "cortex-m3", ""},
	{"esp32",   "xtensa",  "", ""},
};

static string getTypeName(Type *ty) {
	string type_str;
	llvm::raw_string_ostream rso(type_str);
	ty->print(rso);
	return rso.str();
}

static int yyerrorcpp(const string& s, SourceLocation *n) {
	string e = COLOR_RED "semantic error: " COLOR_RESET + s;
	if (n) {
		yylloc.first_line = n->getLineNo();
		yylloc.first_column = n->getColNo();
	}
	return yyerror(e.c_str());
}

static void yywarncpp(const string& s, SourceLocation *n) {
	string e = COLOR_BLUE "semantic warning: " COLOR_RESET + s;
	if (n) {
		yylloc.first_line = n->getLineNo();
		yylloc.first_column = n->getColNo();
	}
	fprintf(stderr, "%s:%d:%d %s\n", 
		build_filename, yylloc.first_line, yylloc.first_column, e.c_str());
}

static RobSymbol *search_symbol(const string& ident, BasicBlock *firstb = NULL, BasicBlock *secondb = NULL) {
	BasicBlock *blocks[] = {firstb, secondb, global_alloc};
	for(BasicBlock *b : blocks) {
		if (b == NULL) 
			continue;
		auto blocksym = tabelasym[b];
		auto var = blocksym.find(ident);
		if (var != blocksym.end())
			return var->second;
	}
	return NULL;
}

template<typename ... Args>
string string_format(const char *format, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, format, args ...) + 1;
    if( size_s <= 0 ) { 
		return "";
	}
    auto size = static_cast<size_t>(size_s);
    unique_ptr<char[]> buf(new char[ size ]);
    snprintf(buf.get(), size, format, args ...);
    return string(buf.get(), buf.get() + size - 1);
}

#include "Node.h"
#include "ArrayElements.h"
#include "AttachInterrupt.h"
#include "BinaryOp.h"
#include "Capsule.h"
#include "CmpOp.h"
#include "Coercion.h"
#include "Delay.h"
#include "Double.h"
#include "Float.h"
#include "Float128.h"
#include "FunctionCall.h"
#include "FunctionDecl.h"
#include "FunctionDeclExtern.h"
#include "FunctionParams.h"
#include "If.h"
#include "Int1.h"
#include "Int8.h"
#include "Int16.h"
#include "Int32.h"
#include "Int64.h"
#include "InPort.h"
#include "Load.h"
#include "LoadArray.h"
#include "LoadMatrix.h"
#include "Matrix.h"
#include "MatrixElements.h"
#include "OutPort.h"
#include "ParamsCall.h"
#include "Print.h"
#include "Program.h"
#include "Return.h"
#include "Stmts.h"
#include "Scalar.h"
#include "Semantic.h"
#include "String.h"
#include "UpdateArray.h"
#include "UpdateMatrix.h"
#include "Array.h"
#include "While.h"
#include "Loop.h"
#include "Pointer.h"
#include "FlipOp.h"
#include "Cast.h"

#include "Visitor.h"
#include "RecursiveVisitor.h"
#include "PrintAstVisitor.h"

#endif

