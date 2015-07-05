%{

#include "node.h"
#include "rob_y.hpp"

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

"printf"				{ return(TOK_PRINT); }

"in"[0-9]+				{ yylval.port = strndup(yytext+2, yyleng-2);
						  return(TOK_IN);
						}

"out"[0-9]+				{ yylval.port = strndup(yytext+3, yyleng-3);
						  return(TOK_OUT);
						}

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

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.ident = strndup(yytext, yyleng); 
						  return(TOK_IDENT); }

"("						{ return('('); }
")"						{ return(')'); }
"{"						{ return('{'); }
"}"						{ return('}'); }

-?[0-9]+\.[0-9]+		{ yylval.number = strndup(yytext, yyleng); 
						  return(TOK_FLOAT); }

-?[0-9]+				{ yylval.number = strndup(yytext, yyleng);
						  return(TOK_INTEIRO); }

"*"						{ return('*'); }
"/"						{ return('/'); }
"+"						{ return('+'); }
"-"						{ return('-'); }
"="						{ return('='); }
";"						{ return(';'); }

%%


