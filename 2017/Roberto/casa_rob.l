%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"

%}

%%

"circulo" {return TOK_CIRC;}
"quadrado" { return TOK_QUAD;}
"retangulo" {return TOK_RET;}
"reta"		{return TOK_RETA;}
"triangulo"	{return TOK_TRI;}
"para"		{return TOK_TO;}
"print" 	{return TOK_PRINT;}

"pinta" {return TOK_PINTA;}

"lado" {return TOK_LADO;}

"+"		{ return TOK_PLUS; }
"-"		{ return TOK_MINUS; }
"*"		{ return TOK_MULTPL; }
"/"		{ return TOK_DIVIDE; }
","		{return ',' ;}
"("		{ return TOK_OPENP; }
")"		{ return TOK_CLOSEP; }
";" 	{ return ';'; }
"{"		{ return TOK_A_C;}
"}"		{return TOK_F_C;}

 /* comentario */
[+-]?[0-9]+			{ yylval.nint = atoi(yytext);
					  return TOK_INTEGER; }


[ \t\n]	{}

.		{ printf("Caracter nao esperado! %s\n",yytext);
		  exit(1);
		}

%%

int yywrap() {
	return 1;
}