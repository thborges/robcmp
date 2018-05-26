%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_MENOR TOK_PLUSPLUS TOK_IDENT
%token TOK_OPENP TOK_CLOSEP
%token TOK_INTEGER TOK_FLOAT
%token TOK_PIXEL TOK_XPIXELS TOK_YPIXELS
%token TOK_FOR
%token EQ_OP NE_OP LT_OP GT_OP LE_OP RE_OP GE_OP TOK_AND TOK_OR




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

stmts : stmts stmt			{ $$->append($2); }
	  | stmt				{ $$ = new Stmts($1); }
	  ;

stmt
    : func                              { $$ = $1; }
    | TOK_IDENT '=' arith_expr ';'      { $$ = new Variable($1, $3); }
    ;
   

func
	: TOK_PIXEL   '[' arith_expr ':' arith_expr ':' TOK_FLOAT':' 'p' '=' TOK_INTEGER ']' ';'     {	
		Node* tam = new Float($7);

		if ($11==0){
			Stmts* quad = new Stmts(new LinearMove($3,$5,new Float(10)));
		
			quad->append(new LinearMove($3, new BinaryOp($5, '+' ,tam)));

			quad->append(new LinearMove(new BinaryOp($3, '+', tam),new BinaryOp($5 ,'+' ,tam)));

			quad->append(new LinearMove(new BinaryOp($3, '+', tam),$5));

			quad->append(new LinearMove($3,$5));

			quad->append(new LinearMove($3,$5,new Float(10)));

			$$=quad;
		}else if($11 == 1){

				Stmts* quad = new Stmts(new LinearMove($3,$5,new Float(3)));
				for(int i=0; i<100; i++){

					tam = new BinaryOp (tam,'-',new Float(0.005));

					quad->append(new LinearMove($3, new BinaryOp($5, '+' ,tam)));

					quad->append(new LinearMove(new BinaryOp($3,'+',tam),new BinaryOp($5 ,'+' ,tam)));

					quad->append(new LinearMove(new BinaryOp($3,'+',tam),$5));

					quad->append(new LinearMove($3,$5));

					quad->append(new LinearMove($3,$5,new Float(3)));

					$$=quad;

			}
		}


		}         
    | TOK_XPIXELS '[' arith_expr ':' arith_expr ':' TOK_FLOAT ':' TOK_INTEGER ']' ';'{
    	Node* tam = new Float($7);
    	Node* x = new Float($7); 
    	

    	Stmts* quad = new Stmts(new LinearMove($3,$5,new Float(10)));
    			quad->append(new LinearMove($3, new BinaryOp($5, '+' ,tam)));
				quad->append(new LinearMove(new BinaryOp($3,'+',tam),new BinaryOp($5 ,'+' ,tam)));
				quad->append(new LinearMove(new BinaryOp($3,'+',tam),$5));
				quad->append(new LinearMove($3,$5));
				quad->append(new LinearMove($3,$5,new Float(3)));
			 	$$=quad;

			 	x = new BinaryOp($3,'+',tam);
				for (int i=1; i<$9; i++) {
					quad->append(new LinearMove(x,$5));
					quad->append(new LinearMove(x,new BinaryOp($5,'+',tam)));
					x = new BinaryOp(x,'+',tam);
					quad->append(new LinearMove(x,new BinaryOp($5,'+',tam)));
					quad->append(new LinearMove(x,$5));
					x = new BinaryOp(x,'-',tam);
					quad->append(new LinearMove(x,$5));
					x = new BinaryOp(x,'+',tam);
					$$=quad;	
			}
				    quad->append(new LinearMove($3,$5,new Float(3)));
    }	
    
    
    | TOK_YPIXELS '[' arith_expr ':' arith_expr ':' TOK_FLOAT ':' TOK_INTEGER ']' ';'{
    	Node* tam = new Float($7);
    	Node* y = new Float($7); 
    	

    	Stmts*  quad = new Stmts(new LinearMove($3,$5,new Float(10)));
    			quad->append(new LinearMove($3, new BinaryOp($5, '+' ,tam)));
				quad->append(new LinearMove(new BinaryOp($3,'+',tam),new BinaryOp($5 ,'+' ,tam)));
				quad->append(new LinearMove(new BinaryOp($3,'+',tam),$5));
				quad->append(new LinearMove($3,$5));
				quad->append(new LinearMove($3,$5,new Float(3)));

			 	$$=quad;

			 	y = new BinaryOp($5,'+',tam);
				for (int i=1;i<$9; i++) {
					quad->append(new LinearMove($3,y));
					quad->append(new LinearMove($3,new BinaryOp(y,'+',tam)));
					y = new BinaryOp(y,'+',tam);
					quad->append(new LinearMove(new BinaryOp($3,'+',tam),y));
					quad->append(new LinearMove(new BinaryOp($3,'+',tam),new BinaryOp(y,'-',tam)));
					y = new BinaryOp(y,'-',tam);
					quad->append(new LinearMove($3,y));
					y = new BinaryOp (y,'+',tam);
					
			}
					quad->append(new LinearMove($3,$5,new Float(3)));
    }
    ;


arith_expr 
     : arith_expr '+' term	    { $$ = new BinaryOp($1, '+', $3); }
	 | arith_expr '-' term	    { $$ = new BinaryOp($1, '-', $3); }
	 | term						{ $$ = $1; }
	 ;

term
     : term '*' factor			{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' factor			{ $$ = new BinaryOp($1, '/', $3); }
	 | factor					{ $$ = $1; }
	 ;

factor 
     : TOK_IDENT				{ $$ = new Load($1); }
     | TOK_INTEGER		   	    { $$ = new Int16($1); }
	 | TOK_FLOAT				{ $$ = new Float($1); }
	 ;

%%

// codigo C

int yyerror(const char *s) {
	printf("error: %s\n", s);
	return 0;
}

/*
int main(int argc, char *argv[]) {
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
	}
	yyparse();
	if (yyin)
		fclose(yyin);
}
*/
