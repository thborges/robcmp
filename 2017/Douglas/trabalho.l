%{

#include <stdio.h>
#include "node.h"
#include "sint.h"

%}
%%

"print" {return TOK_PRINT;}
"linha"	{return TOK_LINHA;}
"arco"	{return TOK_ARC;}
"a"	{return TOK_A;}
 /*"+"	{return TOK_PLUS;}
"-"	{return TOK_MINUS;}
"*"	{return TOK_MULTPL;}
"/"	{return TOK_DIVIDE;}*/
"("	{return '(';}
")"	{return ')';}
";"     {return ';'; } 
","	{return ','; }
 
[+-]?[0-9]+	    {yylval.nint = atoi(yytext);
                    return TOK_INTEGER;}



[-+]?[0-9]+\.[0-9]+	{yylval.nint = atoi(yytext);
                    return TOK_DOUBLE;}

[ \t\n]	{}

.	{yyerror("\n Caracter não esperado %s\n ");
	exit(1);	
	}

%%

int yywrap(){
	return 1;
}

