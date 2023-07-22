
#include "Header.h"
#include "Language_gen_y.hpp"

int errorsfound = 0;
char *build_filename;
char *build_outputfilename;

int USElex(YYSTYPE *yylval_param, location_t *yylloc_param, yyscan_t yyscanner) {
	return MAINlex(yylval_param, yylloc_param, yyscanner);
}

int MAINlex_init(yyscan_t* scanner);
void MAINset_in(FILE *_in_str, yyscan_t yyscanner); 
int MAINlex_destroy(yyscan_t yyscanner);

void yyerror(location_t *loc, yyscan_t scanner, const char *s)
{
	fprintf(stderr, "%s:%d:%d: %s\n", 
		build_filename, loc->first_line, loc->first_column, s);
	errorsfound++;
}

void USEerror(location_t *loc, yyscan_t scanner, const char *s) {
	yyerror(loc, scanner, s);
}

void MAINerror(location_t *loc, yyscan_t scanner, const char *s) {
	yyerror(loc, scanner, s);
}

void yyerrorcpp(const string& s, SourceLocation *n) {
	string e = COLOR_RED "semantic error: " COLOR_RESET + s;
		fprintf(stderr, "%s:%d:%d: %s\n", 
		build_filename, n->getLineNo(), n->getColNo(), s.c_str());
	errorsfound++;
}

void yywarncpp(const string& s, SourceLocation *n) {
	string e = COLOR_BLUE "semantic warning: " COLOR_RESET + s;
	fprintf(stderr, "%s:%d:%d %s\n", 
		build_filename, n->getLineNo(), n->getColNo(), e.c_str());
}

bool parseFile(const char *source) {

    FILE *f = fopen(source, "r");
    if (f == NULL) {
        fprintf(stderr, "Could not open file %s.\n", source);
        return false;
    }

	yyscan_t scanner;
	MAINlex_init(&scanner);
	MAINset_in(f, scanner);
	MAINparse(scanner);
	MAINlex_destroy(scanner);

	if (f)
		fclose(f);
    
    return true;
}

bool parseUseFile(const char *use) {
    return false;
}
