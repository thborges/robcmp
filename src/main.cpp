#include <iostream>

#include "Header.h"

int errorsfound = 0;
extern int yyparse();
extern FILE *yyin;
void print_llvm_ir(const char *target, char opt_level);
Function *AttachInterrupt::fattach = NULL;

// file name
char *build_filename;

int main(int argc, char *argv[]) {

	char optimization = 'z';
	char targetarch[20];
	targetarch[0] = 0;

	// Compila o arquivo passado como parâmetro
	int i = 1;
	while (i < argc) {
		if (strncmp(argv[i], "-O", 2) == 0) {
			if (strlen(argv[1]) > 2)
				optimization = argv[i][2];
		}
		else if (strncmp(argv[i], "-a", 2) == 0) {
			strcpy(targetarch, &argv[i][2]);
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

	print_llvm_ir(targetarch, optimization);

	return 0;
}

