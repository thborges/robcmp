#include <iostream>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>

#include <llvm/Analysis/Passes.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>

#include "Header.h"

int errorsfound = 0;
extern int yyparse();
extern FILE *yyin;

// Program main module
Module *mainmodule;
BasicBlock *mainblock;
BasicBlock *global_alloc;
LLVMContext global_context;

// symbol table
map<BasicBlock*, map<string, Value*>> tabelasym;

// file name
char *build_filename;

// arduino functions
Function *analogWrite;
Function *analogRead;
Function *delay;
Function *delayMicroseconds;
Function *init;
Function *print;
Function *i16div;
Function *AttachInterrupt::fattach = NULL;

int optimization = 1;

int main(int argc, char *argv[]) {

	// Compila o arquivo passado como parâmetro
	int i = 1;
	while (i < argc) {
		if (strncmp(argv[i], "-O", 2) == 0) {
			optimization = atoi(&argv[i][2]);
		}
		else if (strncmp(argv[i], "-A", 2) == 0) {
			//Arquitecture
		}
		else {
			build_filename = argv[i];
			yyin = fopen(build_filename, "r");
			if (yyin == NULL) {
				fprintf(stderr, "Could not open file %s.\n", build_filename);
				exit(1);
			}
		}
		i++;
	}
	yyparse();
	if (yyin)
		fclose(yyin);

	if (errorsfound > 0) {
		fprintf(stderr, "%d error(s) found.\n", errorsfound);
		return errorsfound;
	}

	llvm::legacy::PassManager pm;

	if (optimization >= 1) {
		pm.add(createPromoteMemoryToRegisterPass());
	}

	if (optimization >= 2) {
		pm.add(createInstructionCombiningPass());
		pm.add(createReassociatePass());
		pm.add(createCFGSimplificationPass());
		pm.add(createLICMPass());
		pm.add(createGVNPass());
		pm.add(createSCCPPass());
		pm.add(createCFGSimplificationPass());
		pm.add(createAggressiveDCEPass());
		pm.add(createDeadStoreEliminationPass());
		pm.add(createCFGSimplificationPass());
	}

	// imprime o código intermediário gerado
	pm.add(createPrintModulePass(outs()));

	pm.run(*mainmodule);

	return 0;
}

