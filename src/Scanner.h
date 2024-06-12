
#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "SourceLocation.h"

using namespace std;

static const char *file_not_found = "No such file or directory '%s'.";

typedef void* yyscan_t;
extern int errorsfound;
extern vector<filesystem::path> includeDirs;

void yyerror(location_t *loc, yyscan_t scanner, const char *s);
void USEerror(location_t *loc, yyscan_t scanner, const char *s);
void MAINerror(location_t *loc, yyscan_t scanner, const char *s);
void yyerrorcpp(const string& s, SourceLocation *n, bool semantic);
void yywarncpp(const string& s, SourceLocation *n);

bool parseFile(const string &source);
bool parseUseFile(const string& use, location_t loc);

const filesystem::path* build_file();
