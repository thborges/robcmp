#include <iostream>

#include "Header.h"

int errorsfound = 0;
extern int mainparse();
extern FILE *mainin;
void print_llvm_ir(const char *target, char opt_level);
Function *AttachInterrupt::fattach = NULL;

extern int specparse();
extern FILE *specin;


// file name
char *build_filename;

char *spec_filename;

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
		else if (strncmp(argv[i], "-s", 2) == 0) {
			std::cout << argv[i+1] << std::endl;
			spec_filename = argv[i+1];
			specin = fopen(spec_filename, "r");
			if (specin == NULL) {
				fprintf(stderr, "Could not open file %s.\n", build_filename);
				exit(1);
			}
		}
		else {
			build_filename = argv[i];
			mainin = fopen(build_filename, "r");
			if (mainin == NULL) {
				fprintf(stderr, "Could not open file %s.\n", build_filename);
				exit(1);
			}
		}
		i++;
	}

	specparse();
	if (specin) {
		fclose(specin);
	}

	mainparse();
	if (mainin)
		fclose(mainin);

	if (errorsfound > 0) {
		fprintf(stderr, "%d error(s) found.\n", errorsfound);
		return errorsfound;
	}

	// print_llvm_ir(targetarch, optimization);

	return 0;
}
