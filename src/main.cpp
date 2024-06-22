#include <cstdlib>
#include <cstring>

#include "BackLLVM.h"
#include "Scanner.h"
#include "Program.h"

Program *program = NULL;

int print_llvm_ir(char opt_level);
void setup_target_machine(char opt_level);
bool debug_info;
bool build_dependencies;
char *build_outputfilename;

char *spec_filename;
FILE *specin = NULL;
int speclex_init(yyscan_t* scanner);
void specset_in(FILE *_in_str, yyscan_t yyscanner); 
int speclex_destroy(yyscan_t yyscanner);
int specparse(yyscan_t scanner);

#include <execinfo.h>
#include <unistd.h>
#include <signal.h>
void SIGSEGV_handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char *argv[]) {
	signal(SIGSEGV, SIGSEGV_handler);

	char optimization = 'z';
	const char *targetarch = "";
	build_outputfilename = NULL;
	debug_info = false;
	build_dependencies = false;

	if (argc <= 1) {
		fprintf(stderr, "Syntax: %s -a {", argv[0]);
		for(int t = 1; t < (sizeof(supportedTargets)/sizeof(TargetInfo)); t++) {
			if (t > 1) fprintf(stderr, ",");
			fprintf(stderr, "%s", supportedTargets[t].name);
		}
		fprintf(stderr, "} -I {include_dir} -bdep -g -O{0,1,2,3,s,z,d} -o output.o -s in.spec input.rob\n");
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
		else if (strncmp(argv[i], "-bdep", 5) == 0) {
			build_dependencies = true;
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

	// set current target and basic build types
	setTarget(targetarch);

	if (!buildFileName || !parseFile(buildFileName))
		exit(1);

	if (specin) {
		if (!parseUseFile(spec_filename, {0,0,0,0}, true))
			exit(1);
	}

	setup_target_machine(optimization);

	program->doSemanticAnalysis();
	
	if (errorsfound <= 0)
		program->generate(); 

	if (errorsfound <= 0)
		errorsfound = print_llvm_ir(optimization);

	if (errorsfound > 0)
		fprintf(stderr, "%d error(s) found.\n", errorsfound);

	return errorsfound;
}

