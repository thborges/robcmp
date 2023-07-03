#ifndef __HEADER_H__
#define __HEADER_H__

//#define ENABLE_ARDUINO
//#define ENABLE_PRINT

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
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
  tint8u, tint16u, tint32u, tint64u, thalf, tfloat, tdouble, tldouble,
  __ldt_last};

static const char *LanguageDataTypeNames[__ldt_last] = {"void", "boolean", "char", "int8",
	"int16", "int32", "int64", "unsigned int8", "unsigned int16",
	"unsigned int32", "unsigned int64", "half float", "float",
	"double", "long double"};

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

#include "bison.hpp"

extern int yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern int yycolno;

// Program main module
extern Module *mainmodule;
extern BasicBlock *global_alloc;

extern char* build_filename;
extern char* build_outputfilename;
extern LLVMContext global_context;

#include "SourceLocation.h"

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
	{"stm32",   "thumbv7m-none-eabi", "cortex-m3", ""},
	{"esp32",   "xtensa",  "", ""},
};

static string getTypeName(Type *ty) {
	string type_str;
	llvm::raw_string_ostream rso(type_str);
	ty->print(rso);
	return rso.str();
}

static int yyerrorcpp(const string& s, SourceLocation *n) {
	string e = "semantic error, " + s;
	yylineno = n->getLineNo();
	yycolno = n->getColNo();
	return yyerror(e.c_str());
}

static void yywarncpp(const string& s, SourceLocation *n) {
	string e = "semantic warning, " + s;
	yylineno = n->getLineNo();
	yycolno = n->getColNo();
	fprintf(stderr, "%s:%d:%d %s\n", 
		build_filename, yylineno, yycolno, e.c_str());
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
#include "Half.h"
#include "If.h"
#include "Int1.h"
#include "Int8.h"
#include "Int16.h"
#include "Int32.h"
#include "Int64.h"
#include "InPort.h"
#include "Load.h"
#include "LoadMatrix.h"
#include "LoadVector.h"
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
#include "UpdateVector.h"
#include "Vector.h"
#include "While.h"
#include "Loop.h"
#include "Pointer.h"
#include "FlipOp.h"
#include "Cast.h"

#include "Visitor.h"
#include "RecursiveVisitor.h"
#include "PrintAstVisitor.h"

#endif

