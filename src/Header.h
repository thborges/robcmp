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

// Program main module and IR Builder
extern Module* mainmodule;
extern BasicBlock* global_alloc;
extern LLVMContext global_context;
extern std::unique_ptr<IRBuilder<>> Builder;

#include "SourceLocation.h"

// Debug Info
extern bool debug_info;
extern std::unique_ptr<DIBuilder> DBuilder;
struct DebugInfo {
	DICompileUnit *cunit;
	vector<DIFile *> files;
	vector<DIScope *> scopes;
	void emitLocation(SourceLocation *s);
	void push_scope(DIFile *f, DIScope *);
	void pop_scope();
	DIFile *currFile();
	DIScope *currScope();
};
extern struct DebugInfo RobDbgInfo;

#include "BuildTypes.h"
extern std::unique_ptr<BuildTypes> buildTypes;

#include "Scanner.h"

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
	BasicDataType type;
} FunctionParam;

typedef struct {
	ArrayElements *array;
	unsigned count;
} MatrixElement;

#include "Field.h"

extern char* build_filename;
extern char* build_outputfilename;

// symbol table
#include "RobSymbol.h"
extern map<BasicBlock*, map<string, RobSymbol*>> tabelasym;
static Node* getNodeForIntConst(int64_t i);

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
	const BasicDataType pointerType;
} TargetInfo;

enum SupportedTargets {native, avr328p, stm32f1, esp32, __last_target};
static enum SupportedTargets currentTargetId;
#define currentTarget (supportedTargets[currentTargetId])

static TargetInfo supportedTargets[__last_target] = {
	{"", "", "", "", tint64}, // default target
	{"avr328p", "avr-atmel-none", "atmega328p", "+avr5", tint16},
	{"stm32f1", "thumbv7m-none-eabi", "cortex-m3", "", tint32},
	{"esp32",   "xtensa",  "", "", tint32},
};

static void initTarget(const char *targetarch) {
	currentTargetId = native; //native
	for(int t = native; t < __last_target; t++) {
		if (strcmp(targetarch, supportedTargets[t].name) == 0) {
			currentTargetId = static_cast<enum SupportedTargets>(t);
			break;
		}
	}
	buildTypes = make_unique<BuildTypes>(currentTarget.pointerType);
}

static string getTypeName(Type *ty) {
	string type_str;
	llvm::raw_string_ostream rso(type_str);
	ty->print(rso);
	return rso.str();
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
#include "FunctionImpl.h"
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
#include "Stmts.h"
#include "Program.h"
#include "Return.h"
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
#include "InlineAssembly.h"
#include "Interface.h"
#include "UserType.h"

#include "Visitor.h"
#include "RecursiveVisitor.h"
#include "PrintAstVisitor.h"

static Node* getNodeForIntConst(int64_t i) {
	if (i >= SCHAR_MIN && i <= SCHAR_MAX)
		return new Int8(i);
	else if (i >= SHRT_MIN && i <= SHRT_MAX)
		return new Int16(i);
	else if (i >= INT_MIN && i <= INT_MAX)
		return new Int32(i);
	else
		return new Int64(i);
}

#endif

