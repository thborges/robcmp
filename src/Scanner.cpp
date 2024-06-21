
#include "SourceLocation.h"
#include "Scanner.h"
#include "Program.h"
#include "FlexDependencies.h"
#include "Language_gen_y.hpp"

extern Program *program;

int errorsfound = 0;

vector<filesystem::path> includeDirs;
vector<filesystem::path> buildStack;
stack<filesystem::path> useStack;
vector<yyscan_t> buildStackScanner;
int buildStackCurrent;
bool parseIsCompleted = false;
extern bool build_dependencies;

int USElex(YYSTYPE *yylval_param, location_t *yylloc_param, yyscan_t yyscanner) {
	return MAINlex(yylval_param, yylloc_param, yyscanner);
}

int MAINlex_init(yyscan_t* scanner);
void MAINset_in(FILE *_in_str, yyscan_t yyscanner); 
int MAINlex_destroy(yyscan_t yyscanner);
int USEparse(yyscan_t scanner);

void yyerror(location_t *loc, yyscan_t scanner, const char *s) {
	fprintf(stderr, ":%d:%d: %s\n", 
		loc->first_line, loc->first_column, s);
	errorsfound++;
}

void USEerror(location_t *loc, yyscan_t scanner, const char *s) {
    SourceLocation l(*loc);
	yyerrorcpp(s, &l, false);
}

void MAINerror(location_t *loc, yyscan_t scanner, const char *s) {
    SourceLocation l(*loc);
	yyerrorcpp(s, &l, false);
}

void yyerrorcpp(const string& s, SourceLocation *n, bool semantic) {
    if (n->hasSemanticError())
        return;
    
    string e;
    if (semantic)
	    e = COLOR_RED "semantic error: " COLOR_RESET + s;
    else {
        e = regex_replace(s, regex("syntax error[,:]?"), COLOR_RED "syntax error:" COLOR_RESET);
    }

    fprintf(stderr, "%s:%d:%d: %s\n", 
		n->getFile().c_str(), n->getLineNo(), n->getColNo(), e.c_str());
	errorsfound++;
    n->setSemanticError();
}

void yywarncpp(const string& s, SourceLocation *n) {
	string e = COLOR_BLUE "warning: " COLOR_RESET + s;
	fprintf(stderr, "%s:%d:%d %s\n", 
		n->getFile().c_str(), n->getLineNo(), n->getColNo(), e.c_str());
}

bool parseFile(const string& source) {
	
    filesystem::path file_path(source);
    buildStack.push_back(file_path);
    buildStackCurrent = 0;
	
    // search for use files in the path of build_filename;
	// next in the working dir; next in the -I dirs (right from left)
	includeDirs.push_back(file_path.parent_path());
	includeDirs.push_back("./");

    FILE *f = fopen(file_path.string().c_str(), "r");
    if (f == NULL) {
        cerr << string_format(file_not_found, file_path.string().c_str());
        return false;
    }

	yyscan_t scanner;
	MAINlex_init(&scanner);
    buildStackScanner.push_back(scanner);
	MAINset_in(f, scanner);

    if (program == NULL)
	    program = new Program();
    
	MAINparse(scanner);

	MAINlex_destroy(scanner);
	fclose(f);
    
    return true;
}

FILE *findFile(string file_name, filesystem::path& file_path) {
    FILE *f = NULL;

    // test current dir
    filesystem::path test_path = file_name;
    f = fopen(test_path.string().c_str(), "r");
    if (f) {
        file_path = test_path;
        return f;
    }
    
    // include the dir of the current file
    if (useStack.size() > 0)
        includeDirs.push_back(useStack.top().parent_path());

    for(auto dirit = rbegin(includeDirs); dirit != rend(includeDirs); ++dirit) {
        filesystem::path test_path(*dirit);
        test_path /= file_name;
        f = fopen(test_path.string().c_str(), "r");
        if (f) {
            file_path = test_path;
            break;
        }
    }

    if (useStack.size() > 0)
        includeDirs.pop_back();
    
    return f;
}

bool parseUseFile(const string& use, location_t loc, bool isPath) {

    // search for and open {use}.rob file
    string file_name;
    if (isPath)
        file_name = use;
    else {
        const string sep{filesystem::path::preferred_separator};
        string use_file = regex_replace(use, regex("\\."), sep);
        file_name = use_file + ".rob";
    }
    filesystem::path file_path;
    FILE *f = findFile(file_name, file_path);

    if (f == NULL) {
        if (loc.first_line == 0) // spec file
            cerr << string_format(file_not_found, file_name.c_str());
        else {
            SourceLocation s(loc);
            yyerrorcpp(string_format(file_not_found, file_name.c_str()), &s);
        }
        return false;
    }

    auto it = find(buildStack.begin(), buildStack.end(), file_path);
    if (it != buildStack.end()) {
        // circular dependency
        //#define PRINT_DEPENDENCY_LOOP
        #ifdef PRINT_DEPENDENCY_LOOP
        SourceLocation sl(loc);
        yywarncpp(string_format("circular dependency for %s", file_path.c_str()), &sl);
        while (it != buildStack.end()) {
            fprintf(stderr, "\t%s ->\n", it->c_str());
            it++;
        }
        fprintf(stderr, "\t%s\n", file_path.c_str());
        #endif
        fclose(f);
        return true;
    }

    int buildStackBackup = buildStackCurrent;
    buildStack.push_back(file_path);
    useStack.push(file_path);
    buildStackCurrent = buildStack.size()-1;

    yyscan_t scanner;
	MAINlex_init(&scanner);
    buildStackScanner.push_back(scanner);

	MAINset_in(f, scanner);
    //extern int USEdebug;
    //USEdebug = 1;
    if (build_dependencies) {
        if (debug_info) {
            string bPath = buildStack[buildStackCurrent];
            DIFile *file = DBuilder->createFile(bPath, std::filesystem::current_path().string());
            RobDbgInfo.push_file(file);
        }

        MAINparse(scanner);
        
        if (debug_info)
            RobDbgInfo.pop_file();
    } else
	    USEparse(scanner);

	MAINlex_destroy(scanner);
    fclose(f);

    buildStackCurrent = buildStackBackup;
    buildStackScanner.pop_back();
    //buildStack.pop_back();
    useStack.pop();

    return true;
}

int MAINget_lineno(yyscan_t yyscanner);
int MAINget_column(yyscan_t yyscanner);
