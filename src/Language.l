%{
#include "HeaderGlobals.h"
#include <FlexDependencies.h>
#include "Language_gen_y.hpp"

extern void unescape(char *s);
void update_loc(location_t *yylloc, int lineno, int leng, char *text);

#define YY_USER_ACTION update_loc(yylloc, yylineno, yyleng, yytext);
%}

%option noinput nounput noyywrap
%option yylineno
%option reentrant bison-locations
%option prefix="MAIN"

%x COMMENT

A [a-zA-Z_]
D [0-9]
ID {A}({A}|{D})*
EXP ([Ee][-+]?[0-9]+)?

%%

[ \t\r\n]				{ /* ignore spaces */ }
"/*"					{ yymore(); BEGIN COMMENT; }
<COMMENT>[^*]			{ yymore(); }
<COMMENT>"*"/[^/]		{ yymore(); }
<COMMENT>"*/"			{ BEGIN(INITIAL); }

"//".*$					{ /* line comment */}

"register"				{ return TOK_REGISTER; }
"volatile"				{ return TOK_VOLATILE; }
"const"					{ return TOK_CONST; }
"return"				{ return TOK_RETURN; }
"true"					{ return TOK_TRUE; }
"false"					{ return TOK_FALSE; }
"at"					{ return TOK_AT; }
"asm"					{ return TOK_ASM; }
"type"					{ return TOK_TYPE; }
"interface"				{ return TOK_INTF; }
"implements"			{ return TOK_IMPL; }
"use"					{ return TOK_USE; }

"inline"				{ return TOK_INLINE; }
"noinline"				{ return TOK_NOINLINE; }
"weak"					{ return TOK_WEAK; }
"section"				{ return TOK_SECTION; }
"naked"					{ return TOK_NAKED; }
"signal"				{ return TOK_SIGNAL; }
"debugonly"				{ return TOK_DEBUGONLY; }
"noopt"					{ return TOK_NOOPT; }

"bind"					{ return TOK_BIND; }
"to"					{ return TOK_TO; }
"singleton"				{ return TOK_SINGLETON; }
"transient"				{ return TOK_TRANSIENT; }

"enum"					{ return TOK_ENUM; }

"if"					{ return TOK_IF; }
"else"					{ return TOK_ELSE; }

"while"					{ return TOK_WHILE; }
"loop"					{ return TOK_LOOP; }

"quando"                { return TOK_QUANDO; }
"esta"                  { return TOK_ESTA; }

"and"					{ return TOK_AND; }
"or"					{ return TOK_OR; }

"<<"					{ return TOK_LSHIFT; }
">>"					{ return TOK_RSHIFT; }

"=="					{ return EQ_OP; }
"!="					{ return NE_OP; }
"<="					{ return LE_OP; }
">="					{ return GE_OP; }
"<"						{ return LT_OP; }
">"						{ return GT_OP; }

"["						{ return '['; }
"]"						{ return ']'; }

"("						{ return '('; }
")"						{ return ')'; }

"{"						{ return '{'; }
"}"						{ return '}'; }

"*"						{ return '*'; }
"/"						{ return '/'; }
"+"						{ return '+'; }
"-"						{ return '-'; }
"%"						{ return '%'; }
"="						{ return '='; }

"|"						{ return '|'; }
"&"						{ return '&'; }
"^"						{ return '^'; }
"~"						{ return '~'; }
"!"						{ return '!'; }

":"						{ return ':'; }
"."						{ return '.'; }
","						{ return ','; }
";"						{ return ';'; }

{ID}					{ yylval->ident = strndup(yytext, yyleng); 
						  return TOK_IDENTIFIER; }

{ID}(\.{ID})+			{ yylval->ident = strndup(yytext, yyleng);
						  return TOK_XIDENTIFIER;
						}

[0-9]+\.[0-9]+{EXP}		{ char *aux = strndup(yytext, yyleng);
						  yylval->nfloat = strtof(aux, NULL);
						  free(aux);
						  return TOK_FLOAT; }

[0-9]+\.[0-9]+{EXP}D	{ char *aux = strndup(yytext, yyleng);
						  yylval->ndouble = strtod(aux, NULL);
						  free(aux);
						  return TOK_DOUBLE; }

[0-9]+\.[0-9]+{EXP}LD	{ char *aux = strndup(yytext, yyleng);
						  yylval->nldouble = strtold(aux, NULL);
						  free(aux);
						  return TOK_LDOUBLE; }

"0x"[0-9a-fA-F]+		{ char *aux = strndup(yytext, yyleng);
						  yylval->nint = strtoll(aux, NULL, 16);
						  free(aux);
						  return TOK_INTEGER; }

"0x"[0-9a-fA-F]+[Uu]	{ char *aux = strndup(yytext, yyleng);
						  yylval->unint = strtoull(aux, NULL, 16);
						  free(aux);
						  return TOK_UINTEGER; }

"0b"[0-1]+				{ char *aux = strndup(yytext+2, yyleng-2);
						  yylval->unint = strtoull(aux, NULL, 2);
						  free(aux);
						  return TOK_UINTEGER; }

[0-9]+{EXP}[Uu]			{ char *aux = strndup(yytext, yyleng-1);
						  yylval->unint = (uint64_t)strtod(aux, NULL);
						  free(aux);
						  return TOK_UINTEGER; }

[0-9]+{EXP}				{ char *aux = strndup(yytext, yyleng);
						  yylval->nint = (int64_t)strtod(aux, NULL);
						  free(aux);
						  return TOK_INTEGER; }

\"([^\\\"]|\\.)*\"		{ yylval->str = strndup(yytext+1, yyleng-2);
						  unescape(yylval->str);
						  return TOK_STRING; }

'\\?.'					{ char *aux = strndup(yytext+1, yyleng-2);
						  unescape(aux);
						  yylval->nint = aux[0];
						  free(aux);
						  return TOK_CHAR; }

 /* deixar por último. Caractere não reconhecido pelo alfabeto. */
.						{ yyerror(yylloc, NULL, string_format(COLOR_RED "lexical error:" COLOR_RED " unknown char '%c'.", yytext[0]).c_str()); }

%%

void update_loc(location_t *loc, int lineno, int leng, char *text) {
	loc->first_line = loc->last_line;
	loc->first_column = loc->last_column;
	if (loc->last_line == 0) { // first call
		loc->last_line = lineno;
		loc->last_column += leng;
	} else if (loc->last_line == lineno)
		loc->last_column += leng;
	else {
		loc->last_line = lineno;
		loc->last_column = text + leng - strrchr(text, '\n');
	}
}

#ifdef __MINGW64__
char *strndup(const char *s, size_t n) {
	size_t len = strnlen(s, n);
	char *newstr = (char*)malloc(len+1);
	if (!newstr)
		return NULL;
	newstr[len] = '\0';
	return (char*)memcpy(newstr, s, len);
}
#endif

