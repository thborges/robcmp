%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_PRINT
%token TOK_INTEGER TOK_DOUBLE
%token TOK_ARC TOK_LINHA
%token TOK_A
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR

%union {
        int nint;
        float nfloat;
        Node *node;
        Stmts *stmt;
	Coord *coordenada;
}

%type <node>  programa print funcao
%type <stmt> stmts stmt
%type <nint> TOK_INTEGER
%type <nfloat> TOK_DOUBLE
%type <node>	number
%type <coordenada> cord

%start programa

%%
programa
        : stmts        { Program p;
                        p.generate($1); }
        ;


stmts
        : stmts stmt    	{ $$->append($2); }
        | stmt                 { $$ = new Stmts($1); }
        ;

stmt
	: funcao ';'		{ $$ = new Stmts($1); }
	| print ';'		{ $$ = new Stmts($1); }
        
print
        : TOK_PRINT funcao         { $$ = new Print($2); }
        ;
        
funcao 
        : TOK_LINHA cord TOK_A TOK_LINHA cord     { 
		Stmts *s = new Stmts(new LinearMove($2->getCoordX() , $2->getCoordY(), $2->getCoordZ())); 
		s->append(new LinearMove($5->getCoordX() , $5->getCoordY(), $5->getCoordZ()));
		$$ = s;
	}
	| TOK_ARC cord           { 
		Stmts *s = new Stmts(new ArcMove($2->getCoordX() , $2->getCoordY(), $2->getCoordZ(), $2->getCoordI(), $2->getCoordJ()));
		$$ = s;
	}	
        ;
        
cord 
        : '(' number ',' number ',' number ')'       { $$ = new Coord($2 , $4, $6); }
	| '(' number ',' number ',' number ',' number ',' number ')'	{ $$ = new Coord($2, $4, $6, $8, $10); }
        ;

number   
        : TOK_INTEGER                           { $$ = new Float($1); }
        | TOK_DOUBLE                            { $$ = new Float($1); }
        ;
%%

//codigo C

int yyerror(const char *s) {
        printf("error: %s\n", s);
        return 0;
}

/*int main(int argc, char *argv[]) {
        if (argc > 1) {
                yyin = fopen(argv[1], "r");
         }
         yyparse();
         if (yyin)
                fclose(yyin);
}
*/
