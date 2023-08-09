%{
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

"if"					{ return TOK_IF; }
"else"					{ return TOK_ELSE; }

"while"					{ return TOK_WHILE; }
"loop"					{ return TOK_LOOP; }

"print"					{ return TOK_PRINT; }

"in"[0-9]+				{ yylval->port = strndup(yytext+2, yyleng-2);
						  return TOK_IN;
						}

"out"[0-9]+				{ yylval->port = strndup(yytext+3, yyleng-3);
						  return TOK_OUT;
						}

"stepper"[0-2]+			{ yylval->nint = atoi(strndup(yytext+7, yyleng-7));
						  return TOK_STEPPER;
						}

"servo"					{ return TOK_SERVO; }

"quando"                { return TOK_QUANDO; }
"esta"                  { return TOK_ESTA; }

"delay"					{ return TOK_DELAY; }

"and"					{ return TOK_AND; }
"or"					{ return TOK_OR; }

"!"						{ return '!'; }
"<"						{ return '<'; }
">"						{ return '>'; }

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
"<<"					{ return TOK_LSHIFT; }
">>"					{ return TOK_RSHIFT; }

":"						{ return ':'; }
"."						{ return '.'; }
","						{ return ','; }
";"						{ return ';'; }

{ID}					{ yylval->ident = strndup(yytext, yyleng); 
						  return TOK_IDENTIFIER; }

{ID}(\.{ID})+			{ yylval->ident = strndup(yytext, yyleng);
						  return TOK_XIDENTIFIER;
						}

[0-9]+\.[0-9]+			{ char *aux = strndup(yytext, yyleng);
						  yylval->nfloat = strtof(aux, NULL);
						  free(aux);
						  return TOK_FLOAT; }

[0-9]+\.[0-9]+D			{ char *aux = strndup(yytext, yyleng);
						  yylval->ndouble = strtod(aux, NULL);
						  free(aux);
						  return TOK_DOUBLE; }

[0-9]+\.[0-9]+LD		{ char *aux = strndup(yytext, yyleng);
						  yylval->nldouble = strtold(aux, NULL);
						  free(aux);
						  return TOK_LDOUBLE; }

"0x"[0-9a-fA-F]+		{ char *aux = strndup(yytext, yyleng);
						  yylval->nint = strtoll(aux, NULL, 16);
						  free(aux);
						  return TOK_INTEGER; }

"0b"[0-1]+				{ char *aux = strndup(yytext+2, yyleng-2);
						  yylval->nint = strtoll(aux, NULL, 2);
						  free(aux);
						  return TOK_INTEGER; }

[0-9]+					{ char *aux = strndup(yytext, yyleng);
						  yylval->nint = strtoll(aux, NULL, 10);
						  free(aux);
						  return TOK_INTEGER; }

\"([^\\\"]|\\.)*\"		{ yylval->str = strndup(yytext+1, yyleng-2);
						  unescape(yylval->str);
						  return TOK_STRING; }

'\\?.'					{ char *aux = strndup(yytext+1, yyleng-2);
						  unescape(aux);
						  yylval->nint = aux[0];
						  free(aux);
						  return TOK_INTEGER; }

 /* deixar por último. Caractere não reconhecido pelo alfabeto. */
.						{ yyerror(yylloc, NULL, COLOR_RED "lexical error:" COLOR_RED " caractere nao pertence ao alfabeto da linguagem:"); }

%%

void update_loc(location_t *loc, int lineno, int leng, char *text) {
	loc->first_line = loc->last_line;
	loc->first_column = loc->last_column;
	if (loc->last_line == lineno)
		loc->last_column += leng;
	else {
		loc->last_line = lineno;
		loc->last_column = text + leng - strrchr(text, '\n');
	}
}
