#include <iostream>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>

#include <llvm/Analysis/Passes.h>
#include <llvm/Transforms/Scalar.h>

#include "node.h"

extern int yyparse();
extern FILE *yyin;

// Program main module
Module *mainmodule;

// symbol table
map<string, AllocaInst*> tabelasym;

// arduino functions
Function *analogWrite;
Function *analogRead;
Function *delay;
Function *init;


int main(int argc, char *argv[]) {

	// Compila o arquivo passado como parâmetro
	if (argc > 1)
       	yyin = fopen(argv[1], "r");
   	yyparse();
   	if (yyin)
   		fclose(yyin);

	llvm::legacy::PassManager pm;

	pm.add(createPromoteMemoryToRegisterPass());
	pm.add(createInstructionCombiningPass());
    pm.add(createReassociatePass());
	pm.add(createCFGSimplificationPass());
	/*pm.add(createLICMPass());
	pm.add(createGVNPass());
	pm.add(createSCCPPass());
	pm.add(createCFGSimplificationPass());
	pm.add(createAggressiveDCEPass());
	pm.add(createDeadStoreEliminationPass());
	pm.add(createCFGSimplificationPass());*/

	// imprime o código intermediário gerado
	pm.add(createPrintModulePass(outs()));

	pm.run(*mainmodule);

}

