%{

#include "node.h"
#include "bison.hpp"

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

"print"					{ return(TOK_PRINT); }

"in"[0-9]+				{ yylval.port = strndup(yytext+2, yyleng-2);
						  return(TOK_IN);
						}

"out"[0-9]+				{ yylval.port = strndup(yytext+3, yyleng-3);
						  return(TOK_OUT);
						}

"stepper"[0-2]+			{ yylval.nint = atoi(strndup(yytext+7, yyleng-7));
						  return(TOK_STEPPER);
						}

"servo"					{ return(TOK_SERVO); }

"delay"					{ return(TOK_DELAY); }
"if"					{ return(TOK_IF); }
"else"					{ return(TOK_ELSE); }
"while"					{ return(TOK_WHILE); }
"=="					{ return(EQ_OP); }
"!="					{ return(NE_OP); }
"<="					{ return(LE_OP); }
">="					{ return(GE_OP); }
">"						{ return(GT_OP); }
"<"						{ return(LT_OP); }
"and"					{ return(TOK_AND); }
"or"					{ return(TOK_OR); }
"function"				{ return(TOK_FUNC); }
"return"				{ return(TOK_RETURN); }

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.ident = strndup(yytext, yyleng); 
						  return(TOK_IDENT); }

"("						{ return('('); }
")"						{ return(')'); }
"{"						{ return('{'); }
"}"						{ return('}'); }

-?[0-9]+\.[0-9]+		{ yylval.nfloat = atof(yytext); 
						  return(TOK_FLOAT); }

-?[0-9]+				{ yylval.nint = atoi(yytext);
						  return(TOK_INTEIRO); }

"*"						{ return('*'); }
"/"						{ return('/'); }
"+"						{ return('+'); }
"-"						{ return('-'); }
"%"						{ return('%'); }
"="						{ return('='); }
";"						{ return(';'); }

\"([^\\\"]|\\.)*\"		{ yylval.str = strndup(yytext+1, yyleng-2);
						  unescape(yylval.str);
						  return(TOK_STRING); }

 /* deixar por último. Caractere não reconhecido pelo alfabeto. */
.						{ yyerror("lexical error, caractere nao pertence ao alfabeto da linguagem:"); }

%%


