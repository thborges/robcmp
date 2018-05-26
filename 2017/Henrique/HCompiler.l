%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"
//#include "limite.c"


%}

%%

"circulo"   {return TOK_CIRCULO;}	
"quadrado"  {return TOK_QUADRADO;}
"triangulo" {return TOK_TRIANGULO;}
"retangulo" {return TOK_RETANGULO;}
"pentagono" {return TOK_PENTAGONO;}
"losango"   {return TOK_LOSANGO;}
"hexagono"  {return TOK_HEXAGONO;}
"trapezio"  {return TOK_TRAPEZIO;}

"iniciarCoords"     { return(TOK_INICIARCOORDS); }
"line"		{ return(TOK_LINE); }
"arc" 		{ return(TOK_ARC); }

"if"		{ return TOK_IF; }
"while"		{ return TOK_WHILE; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"="		{ return '='; }
"/"		{ return '/'; }
"("		{ return '('; }
")"		{ return ')'; }
","		{ return ','; } 
";"		{ return ';'; }
"{"		{ return '{'; }
"}"		{ return '}'; }
"=="					{ return(EQ_OP); }
"!="					{ return(NE_OP); }
"<="					{ return(LE_OP); }
">="					{ return(GE_OP); }
">"					{ return(GT_OP); }
"<"					{ return(LT_OP); }
"and"					{ return(TOK_AND); }
"or"					{ return(TOK_OR); }



 /* comentario */
[+-]?[0-9]+			{ yylval.nint = atoi(yytext); 
					  return TOK_INTEGER; }

[+-]?[0-9]+\.[0-9]+	{ yylval.nfloat = atof(yytext);
					  return TOK_DOUBLE; }

 								

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


