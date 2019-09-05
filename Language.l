%{

#include "src/Header.h"
#include "src/bison.hpp"

extern void unescape(char *s);

%}

%option yylineno
%x COMMENT

%%

[ \t\n\r]				{ /* espaços */ }
"/*"					{ yymore(); BEGIN COMMENT; }
<COMMENT>[^*]			{ yymore(); }
<COMMENT>"*"/[^/]		{ yymore(); }
<COMMENT>"*/"			{ BEGIN(INITIAL); }

"//".*$					{ fprintf(stderr, "Comentario: %s\n", yytext); /* comentario de linha */}

"function"				{ return TOK_FUNCTION; }
"return"				{ return TOK_RETURN; }

"if"					{ return TOK_IF; }
"else"					{ return TOK_ELSE; }

"while"					{ return TOK_WHILE; }

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

":"						{ return ':'; }
","						{ return ','; }
";"						{ return ';'; }

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.ident = strndup(yytext, yyleng); 
						  return TOK_IDENTIFIER; }

-?[0-9]+\.[0-9]+		{ yylval.nfloat = atof(yytext); 
						  return TOK_FLOAT; }

-?[0-9]+				{ yylval.nint = atoi(yytext);
						  return TOK_INTEGER; }

\"([^\\\"]|\\.)*\"		{ yylval.str = strndup(yytext+1, yyleng-2);
						  unescape(yylval.str);
						  return TOK_STRING; }

 /* deixar por último. Caractere não reconhecido pelo alfabeto. */
.						{ yyerror("lexical error, caractere nao pertence ao alfabeto da linguagem:"); }

%%


