
#pragma once

#include <string>
#include "SourceLocation.h"

using namespace std;

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

typedef void* yyscan_t;
extern int errorsfound;
extern char *build_filename;

void yyerror(location_t *loc, yyscan_t scanner, const char *s);
void USEerror(location_t *loc, yyscan_t scanner, const char *s);
void MAINerror(location_t *loc, yyscan_t scanner, const char *s);
void yyerrorcpp(const string& s, SourceLocation *n);
void yywarncpp(const string& s, SourceLocation *n);

bool parseFile(const char *source);
bool parseUseFile(const char *use);
