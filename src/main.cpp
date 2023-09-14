#include <iostream>
#include <cstdlib>
#include <cstring>

#include "BackLLVM.h"
#include "Scanner.h"
#include "Program.h"

void print_llvm_ir(char opt_level);
bool debug_info;
extern char *build_outputfilename;

char *spec_filename;
FILE *specin = NULL;
int speclex_init(yyscan_t* scanner);
void specset_in(FILE *_in_str, yyscan_t yyscanner); 
int speclex_destroy(yyscan_t yyscanner);
int specparse(yyscan_t scanner);

int main(int argc, char *argv[]) {

	char optimization = 'z';
	const char *targetarch = "";
	build_outputfilename = NULL;
	debug_info = false;

	if (argc <= 1) {
		fprintf(stderr, "Syntax: %s -a {", argv[0]);
		for(int t = 1; t < (sizeof(supportedTargets)/sizeof(TargetInfo)); t++) {
			if (t > 1) fprintf(stderr, ",");
			fprintf(stderr, "%s", supportedTargets[t].name);
		}
		fprintf(stderr, "} -I {include_dir} -g -O{1,2,3,s,z} -o output_file input_file\n");
		return 1;
	}

	// Compila o arquivo passado como parâmetro
	const char* buildFileName = NULL;
	FILE *source = NULL;
	int i = 1;
	while (i < argc) {
		if (strncmp(argv[i], "-O", 2) == 0) {
			if (strlen(argv[i]) > 2)
				optimization = argv[i][2];
		}
		else if (strncmp(argv[i], "-a", 2) == 0) { // target arch
			targetarch = argv[++i];
		}
		else if (strncmp(argv[i], "-g", 2) == 0) { // debug
			debug_info = true;
		}
		else if (strncmp(argv[i], "-o", 2) == 0) { // output
			if (i+1 < argc)
				build_outputfilename = argv[++i];
		}
		else if (strncmp(argv[i], "-I", 2) == 0) { // include dirs
			if (i+1 < argc)
				includeDirs.push_back(argv[++i]);
		}
		else if (strncmp(argv[i], "-s", 2) == 0) {
			spec_filename = argv[++i];
			specin = fopen(spec_filename, "r");
			if (specin == NULL) {
				fprintf(stderr, "Could not open file %s.\n", spec_filename);
				exit(1);
			}
		}
		else {
			buildFileName = argv[i];
		}
		i++;
	}

	if (specin) {
		yyscan_t scanner;
		speclex_init(&scanner);
		specset_in(specin, scanner);
		specparse(scanner);
		speclex_destroy(scanner);
		fclose(specin);
	}

	// set current target and basic build types
	setTarget(targetarch);

	if (!parseFile(buildFileName))
		exit(1);

	if (errorsfound > 0) {
		fprintf(stderr, "%d error(s) found.\n", errorsfound);
		return errorsfound;
	}

	print_llvm_ir(optimization);

	return 0;
}

