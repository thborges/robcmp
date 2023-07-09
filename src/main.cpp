#include <iostream>
#include <cstdlib>

#include "Header.h"

int errorsfound = 0;
int yycolno = 0;
int yycolnew = 0;
extern int yyparse();
extern FILE *yyin;
void print_llvm_ir(const char *target, char opt_level);
Function *AttachInterrupt::fattach = NULL;

// file name
char *build_filename;
char *build_outputfilename;

int main(int argc, char *argv[]) {

	char optimization = 'z';
	const char *targetarch = "";
	build_outputfilename = NULL;

	if (argc <= 1) {
		fprintf(stderr, "Syntax: %s -O{1,2,3,s,z} -a {", argv[0]);
		for(int t = 1; t < (sizeof(supportedTargets)/sizeof(TargetInfo)); t++) {
			if (t > 1) fprintf(stderr, ",");
			fprintf(stderr, "%s", supportedTargets[t].name);
		}
		fprintf(stderr, "} -o output_file input_file\n");
		return 1;
	}

	// Compila o arquivo passado como parâmetro
	int i = 1;
	while (i < argc) {
		if (strncmp(argv[i], "-O", 2) == 0) {
			if (strlen(argv[1]) > 2)
				optimization = argv[i][2];
		}
		else if (strncmp(argv[i], "-a", 2) == 0) {
			targetarch = argv[++i];
		}
		else if (strncmp(argv[i], "-o", 2) == 0) {
			build_outputfilename = argv[++i];
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

