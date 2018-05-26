%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"

%}

%%

[ \t\n\r]				{ /* espaços */ }



"retangulo" 				{return TOK_RETANGULO;}
"circulo" 					{return TOK_CIRCULO;}
"triangulo" 				{return TOK_TRIANGULO;}
"print" 					{return TOK_PRINT; }
"while" 					{return TOK_WHILE; }
"*"						{ return('*'); }
"/"						{ return('/'); }
"+"						{ return('+'); }
"-"						{ return('-'); }
"="						{ return('='); }
";"						{ return(';'); }
"="						{ return '='; }
"<"	   				    { return TOK_MENOR; }
"++"	   			    { return TOK_PLUSPLUS; }
"{"		                { return '{'; }
"}"		                { return '}'; }
"("                     { return '('; }
")"                     { return ')'; }		
","                     { return ','; }		  

[+-]?[0-9]+			{ yylval.nint = atoi(yytext);
					  return TOK_INTEGER; }

[+-]?[0-9]+\.[0-9]+	{ yylval.nfloat = atof(yytext);
					  return TOK_FLOAT; }

[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.ident = strndup(yytext, yyleng); 
						  return(TOK_IDENT); }

[ \t\n]	{}

.		{printf ("\n Caracter nao esperado %s\n", yytext);
		  exit(1);
		}

%%

int yywrap() {
	return 1;
}
