%{

#include "Header.h"
#include "bison.hpp"

extern void unescape(char *s);

extern int yycolno;

static void update_loc() {
	yylloc.first_line = yylineno;
	yylloc.last_line = yylineno;
	yylloc.first_column = yycolno;
	yylloc.last_column = yycolno + yyleng - 1;
	yycolno += yyleng;
}
	
#define YY_USER_ACTION update_loc();

%}

%option yylineno
%x COMMENT

%%

[ \t\r]					{ /* ignore spaces */ }
[\n]					{ yycolno = 0; }
"/*"					{ yymore(); BEGIN COMMENT; }
<COMMENT>[^*]			{ yymore(); }
<COMMENT>"*"/[^/]		{ yymore(); }
<COMMENT>"*/"			{ BEGIN(INITIAL); }

"//".*$					{ /* line comment */}

"register"				{ return TOK_REGISTER; }
"volatile"				{ return TOK_VOLATILE; }
"const"					{ return TOK_CONST; }
"void"					{ return TOK_VOID; }
"bool"					{ return TOK_FBOOL; }
"char"					{ return TOK_FCHAR; }
"int8"					{ return TOK_FINT8; }
"int16"					{ return TOK_FINT16; }
"int32"					{ return TOK_FINT32; }
"int64"					{ return TOK_FINT64; }
"float"					{ return TOK_FFLOAT; }
"double"				{ return TOK_FDOUBLE; }
"long"					{ return TOK_FLONG; }
"unsigned"				{ return TOK_FUNSIGNED; }
"return"				{ return TOK_RETURN; }
"true"					{ return TOK_TRUE; }
"false"					{ return TOK_FALSE; }
"at"					{ return TOK_AT; }
"asm"					{ return TOK_ASM; }

"if"					{ return TOK_IF; }
"else"					{ return TOK_ELSE; }

"while"					{ return TOK_WHILE; }
"loop"					{ return TOK_LOOP; }

"print"					{ return TOK_PRINT; }

"in"[0-9]+				{ yylval.port = strndup(yytext+2, yyleng-2);
						  return TOK_IN;
						}

"out"[0-9]+				{ yylval.port = strndup(yytext+3, yyleng-3);
						  return TOK_OUT;
						}

"stepper"[0-2]+			{ yylval.nint = atoi(strndup(yytext+7, yyleng-7));
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

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.ident = strndup(yytext, yyleng); 
						  return TOK_IDENTIFIER; }

[0-9]+\.[0-9]+			{ char *aux = strndup(yytext, yyleng);
						  yylval.nfloat = strtof(aux, NULL);
						  free(aux);
						  return TOK_FLOAT; }

[0-9]+\.[0-9]+D			{ char *aux = strndup(yytext, yyleng);
						  yylval.ndouble = strtod(aux, NULL);
						  free(aux);
						  return TOK_DOUBLE; }

[0-9]+\.[0-9]+LD		{ char *aux = strndup(yytext, yyleng);
						  yylval.nldouble = strtold(aux, NULL);
						  free(aux);
						  return TOK_LDOUBLE; }

"0x"[0-9a-fA-F]+		{ char *aux = strndup(yytext, yyleng);
						  yylval.nint = strtoll(aux, NULL, 16);
						  free(aux);
						  return TOK_INTEGER; }

"0b"[0-1]+				{ char *aux = strndup(yytext+2, yyleng-2);
						  yylval.nint = strtoll(aux, NULL, 2);
						  free(aux);
						  return TOK_INTEGER; }

[0-9]+					{ char *aux = strndup(yytext, yyleng);
						  yylval.nint = strtoll(aux, NULL, 10);
						  free(aux);
						  return TOK_INTEGER; }

\"([^\\\"]|\\.)*\"		{ yylval.str = strndup(yytext+1, yyleng-2);
						  unescape(yylval.str);
						  return TOK_STRING; }

 /* deixar por último. Caractere não reconhecido pelo alfabeto. */
.						{ yyerror("lexical error, caractere nao pertence ao alfabeto da linguagem:"); }

%%


