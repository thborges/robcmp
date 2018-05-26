%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"

%}

%%

"="		{ return TOK_IGUAL;}
"+"		{ return TOK_PLUS; } 
"-"		{ return TOK_MINUS; }
"*"		{ return TOK_MULTPL; }
"/"		{ return TOK_DIVIDE; }
"("		{ return TOK_OPENP; }
")"		{ return TOK_CLOSEP; }
";"		{ return ';';}
","		{ return ',';}
"linha"		{ return TOK_LINHA;}
"circulo"	{ return TOK_CIRCULO;}
"losango"	{ return TOK_LOSANGO;}
"raio"		{ return TOK_RAIO;}
"Dm"		{ return TOK_DM;}
"dm"		{ return TOK_dM;}
"retangulo"	{ return TOK_RETANGULO;}
"base"		{ return TOK_BASE;}
"altura"	{ return TOK_ALTURA;}
"id"		{ return TOK_ID;}





 /* comentario */
[+-]?[0-9]+		{ yylval.nint = atoi(yytext);
			return TOK_INTEGER; }

[+-]?[0-9]+\.[0-9]+	{yylval.nfloat = atof(yytext);
			return TOK_DOUBLE; }

[ \t\n]	{}

.		{ yyerror("Caracter nao esperado");
		  exit(1);
		}

%%

int yywrap() {
	return 1;
}

