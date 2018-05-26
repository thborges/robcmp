%{

#include <stdio.h>
#include "node.h"
#include "sintatico.h"

%}

%%

"quadrado"      { return TOK_Q; }
"quadrado_p"    { return TOK_Q_P; }
"linha"         { return TOK_L; }
"circulo"       { return TOK_C; }
"circulo_p"     { return TOK_C_P; }
"retangulo"     { return TOK_R; }
"triangulo"     { return TOK_T; }
"triangulo_eq"  { return TOK_T_E; }
"cabelo"        { return TOK_CABELO; }
"braco"         { return TOK_BRACO; }
"+"             { return TOK_PLUS; }
"-"             { return TOK_MINUS; }
"*"             { return TOK_MULTPL; }
"/"             { return TOK_DIVIDE; }
"("             { return TOK_OPENP; }
")"             { return TOK_CLOSEP; }
";"             { return ';'; }
","             { return ','; }
"|"             { return '|'; }
"="             { return '='; }
"lado"          { return TOK_LADO; }
"raio"          { return TOK_RAIO; }
"largura"       { return TOK_LARG; }
"altura"        { return TOK_ALT;  }



[+]?[0-9]+                { yylval.nint = atoi(yytext);
                           return TOK_INTEGER;}

[+-]?[0-9]+\.[0-9]+	  { yylval.nfloat = atof(yytext);
					  return TOK_FLOAT; }

[ \t\n] {}

.       {yyerror ("\n Caracter nao esperado \n");
        exit(1);
        }

%%

int yywrap (){
     return 1;
}


