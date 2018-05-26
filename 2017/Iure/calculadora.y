%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_PRINT TOK_RETANGULO TOK_TRIANGULO TOK_CIRCULO TOK_WHILE TOK_IDENT
%token TOK_PLUS TOK_MINUS TOK_MULTPL TOK_DIVIDE TOK_MENOR TOK_MAIOR TOK_VAR TOK_PLUSPLUS
%token TOK_INTEGER TOK_FLOAT
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR

%union {
        int nint;
        float nfloat;
        Node *node;
        Stmts *stmt;
	char *ident;
}

%type <node> term arith_expr factor programa stmt func
%type <stmt> stmts
%type <nint> TOK_INTEGER
%type <nfloat> TOK_FLOAT
%type <ident> TOK_IDENT

%start programa

%%
programa : stmts    { Program p;
                      p.generate($1); }
	 ;

stmts   : stmts stmt    			{ $$->append($2); }
		| stmt             			{ $$ = new Stmts($1); }
        ;

stmt	: func 					{ $$ = $1; }
		| TOK_IDENT '=' arith_expr ';'  	{ $$ = new Variable($1, $3); }
		| TOK_IDENT TOK_PLUSPLUS ';'	
		| TOK_VAR TOK_IDENT ';'
		;

func	: TOK_RETANGULO '(' arith_expr ',' arith_expr ',' arith_expr ',' arith_expr ')' ';' {
		Stmts* quad = new Stmts(new LinearMove($3, $5, new Float(5)));
		quad->append(new LinearMove($3, $5, new Float(0)));
		quad->append(new LinearMove(new BinaryOp($3, '+', $7), $5, new Float(0)));
		quad->append(new LinearMove(new BinaryOp($3, '+', $7), new BinaryOp($5, '+' ,$9), new Float(0)));
		quad->append(new LinearMove($3, new BinaryOp($5, '+' ,$9), new Float(0)));
		quad->append(new LinearMove($3, $5, new Float(0)));
		quad->append(new LinearMove($3, $5, new Float(5)));
		$$=quad;}			

	| TOK_TRIANGULO '(' arith_expr ',' arith_expr ',' TOK_INTEGER ',' arith_expr ')' ';'{
		if($7 == 1){
		Stmts* quad = new Stmts(new LinearMove($3, $5, new Float(5)));
		quad->append(new LinearMove($3, $5, new Float(0)));
		quad->append(new LinearMove(new BinaryOp($3, '+', $9), $5, new Float(0)));
		quad->append(new LinearMove(new BinaryOp($3, '+',new BinaryOp($9, '/', new Float(2))), new BinaryOp($5, '+' ,new BinaryOp($9, '/', new Float(2))), new Float(0)));
		quad->append(new LinearMove($3, $5, new Float(0)));
		$$=quad;
		}
		else if ($7 == 2) {
		Stmts* quad = new Stmts(new LinearMove($3, $5, new Float(5)));
		quad->append(new LinearMove($3, $5, new Float(0)));
		quad->append(new LinearMove(new BinaryOp($3, '+', $9), $5, new Float(0)));
		quad->append(new LinearMove(new BinaryOp($3, '+',new BinaryOp($9, '/', new Float(2))), new BinaryOp($5, '-' ,new BinaryOp($9, '/', new Float(2))), new Float(0)));
		quad->append(new LinearMove($3, $5, new Float(0)));
		quad->append(new LinearMove($3, $5, new Float(5)));
		$$=quad;
		}
	}
	| TOK_CIRCULO '(' arith_expr ',' arith_expr ',' arith_expr ')' ';'
	| TOK_WHILE '(' arith_expr TOK_MENOR arith_expr ')' '{' stmts '}' { $$ = new While($3, $5); }			
	; 

        
arith_expr : arith_expr '+' term			{ $$ = new BinaryOp($1, '+', $3); }
	 | arith_expr '-' term			{ $$ = new BinaryOp($1, '-', $3); }
	 | term						{ $$ = $1; }
	 ;

term : term '*' factor		{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' factor		{ $$ = new BinaryOp($1, '/', $3); }
	 | factor				{ $$ = $1; }
	 ;

factor : 
           | TOK_IDENT			{ $$ = new Load($1); }
	   | TOK_INTEGER		{ $$ = new Int16($1); }
	   | TOK_FLOAT			{ $$ = new Float($1); }
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
