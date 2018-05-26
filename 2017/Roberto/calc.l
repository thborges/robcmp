 /*Aula Pratica de compiladores 16/05/2017 --- Douglas Neves Silva*/
%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"
%}
%%
"*"	{return TOK_MULTPL;}
"/"	{return TOK_DIVIDE;}
"("	{return TOK_OPEN;}
")"	{return TOK_CLOSEP;}
"print" {return TOK_PRINT; }
"+"	{return TOK_PLUS;}
"-"	{return TOK_MINUS;}
";"     {return ';'; }

[+-]?[0-9]+	    {yylval.nint = atoi(yytext);
                    return TOK_INTEGER;}

[-+]?[0-9]+\.[0-9]+	{yylval.nfloat = atof(yytext);
                    return TOK_DOUBLE;}

[ \t\n]	{}

.	{yyerror("\n Caracter não esperado %s\n ");
	exit(1);	
	}

%%

int yywrap(){
	return 1;
}


