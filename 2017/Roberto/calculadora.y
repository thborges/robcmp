%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_PRINT
%token TOK_PLUS TOK_MINUS TOK_MULTPL TOK_DIVIDE 
%token TOK_OPEN TOK_CLOSEP
%token TOK_INTEGER TOK_DOUBLE
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR

%union {
        int nint;
        float nfloat;
        Node *node;
        Stmts *stmt;
}

%type <node> term arith_expr factor programa print
%type <stmt> stmts
%type <nint> TOK_INTEGER
%type <nfloat> TOK_DOUBLE

%start programa

%%
programa
        : stmts        { Program p;
                        p.generate($1); }
        ;

stmts
        : stmts print ';'       { $1->append($2); $$ = $1; }
        | print ';'             { $$ = new Stmts($1); }
        ;
        
print
        : TOK_PRINT arith_expr         { $$ = new Print($2); }
        ;
        
arith_expr 
        : arith_expr TOK_PLUS term      { $$ = new BinaryOp($1, '+', $3); }
	| arith_expr TOK_MINUS term      { $$ = new BinaryOp($1, '-', $3); }
        | term                          { $$ = $1; }
        ;
        
term 
        : term TOK_MULTPL factor        { $$ = new BinaryOp($1, '*', $3); }
	| term TOK_DIVIDE factor        { $$ = new BinaryOp($1, '/', $3); }
        | factor                        { $$ = $1; }
        ;

factor   
        : TOK_OPEN arith_expr TOK_CLOSEP        { $$ = $2; }
        | TOK_INTEGER                           { $$ = new Int32($1); }
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

