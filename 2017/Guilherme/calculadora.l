%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"
#include "roman.h"

%}

%%

"print"	{ return TOK_PRINT; }
"while"		{ return TOK_WHILE; }
"if"		{ return TOK_IF; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"="		{ return '='; }
"/"		{ return '/'; }
"("		{ return '('; }
")"		{ return ')'; }
";"		{ return ';'; }
"{"		{ return '{'; }
"}"		{ return '}'; }
"=="					{ return(EQ_OP); }
"!="					{ return(NE_OP); }
"<="					{ return(LE_OP); }
">="					{ return(GE_OP); }
">"						{ return(GT_OP); }
"<"						{ return(LT_OP); }
"and"					{ return(TOK_AND); }
"or"					{ return(TOK_OR); }



 /* comentario */
[+-]?[0-9]+			{ yylval.nint = atoi(yytext);
					  return TOK_INTEGER; }

[+-]?[0-9]+\.[0-9]+	{ yylval.nfloat = atof(yytext);
					  return TOK_DOUBLE; }

(M{0,3})(D?C{0,3}|C[DM])(L?X{0,3}|X[LC])(V?I{0,3}|I[VX]) { yylval.nint = roman_parser(yytext);
								return TOK_INTEGER; }

[a-zA-Z_][a-zA-Z0-9_]*		{ yylval.ident = strndup(yytext, yyleng); 
						  return(TOK_IDENT); }

[ \t\n]	{}

.		{ yyerror("Caracter nao esperado.");
		  exit(1);
		}

%%

//int yywrap() {
//	return 1;
//}


