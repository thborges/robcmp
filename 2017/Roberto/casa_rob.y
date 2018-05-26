%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_PLUS TOK_MINUS TOK_MULTPL TOK_DIVIDE TOK_CIRC TOK_RET TOK_RETA TOK_TRI TOK_QUAD TOK_TO
%token TOK_OPENP TOK_CLOSEP TOK_A_C TOK_F_C TOK_PRINT TOK_PINTA TOK_LADO
%token TOK_INTEGER 
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR

%union {
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;
	Coord *coord_field;
}

%type <node>  arith_expr factor programa circulo quadrado reta triang retangulo stmt print expr pinta
%type <coord_field> coordD
%type <nint> TOK_INTEGER
%type <stmt> stmts
%start programa

%%

programa : stmts 						{ Program p;
										  p.generate($1); }
		 ;

stmts : stmts stmt {$1->append($2); }
	| stmt			{$$ = new Stmts($1);}

stmt
	:circulo ';'                        {$$ = new Capsule($1);}
    |retangulo ';'						{$$ = new Capsule($1);}
	|quadrado	';'                     {$$ = new Capsule($1);}
    |reta ';'                           {$$ = new Capsule($1);}
	|triang ';'                         {$$ = new Capsule($1);}
	|pinta ';'							{$$ = new Capsule($1);}
	;

print
        : TOK_PRINT arith_expr         { $$ = new Print($2); }
		
        ;

circulo
        :TOK_CIRC TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP       {Stmts *bloco = new Stmts( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(1))); 
																					 bloco->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																					 bloco->append(	new ArcMove($3->getCoordX(),$3->getCoordY(), new Float(0), $7->getCoordX(), $7->getCoordY()));
																					 $$ = bloco;			}
        ;
reta
    :TOK_RETA TOK_OPENP coordD TOK_CLOSEP TOK_TO TOK_OPENP coordD TOK_CLOSEP          { Stmts *bloco = new Stmts( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(1))); 
																					 	bloco->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																						bloco ->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																					   	bloco->append( new LinearMove($7->getCoordX(), $7->getCoordY(), new Float(0)));
																					   	$$ = bloco;
																					   }
    ;
retangulo
    :TOK_RET  TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP
													            {Stmts *bloco = new Stmts( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(1))); 
																 bloco->append( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove( $7->getCoordX(), $7->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove($11->getCoordX(), $11->getCoordY(), new Float(0)));
                                                                 bloco->append( new LinearMove($15->getCoordX(), $15->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																 $$ = bloco;
																 }
    ;
quadrado
    : TOK_QUAD TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP ',' TOK_OPENP coordD TOK_CLOSEP
													            {Stmts *bloco = new Stmts( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(1))); 
																 bloco->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																 bloco->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove( $7->getCoordX(), $7->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove($11->getCoordX(), $11->getCoordY(), new Float(0)));
                                                                 bloco->append( new LinearMove($15->getCoordX(), $15->getCoordY(), new Float(0)));
																 bloco->append( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
																 $$ = bloco;
																 }
    ;
triang
    :TOK_TRI   TOK_OPENP   coordD   TOK_CLOSEP   TOK_TO   TOK_OPENP coordD  TOK_CLOSEP TOK_TO TOK_OPENP coordD TOK_CLOSEP    
									{Stmts *bloco = new Stmts( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(1))); 
									  bloco->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
										bloco->append( new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
									 bloco->append(new LinearMove($7->getCoordX(), $7->getCoordY(), new Float(0)));
									 bloco->append( new LinearMove($11->getCoordX(), $11->getCoordY(), new Float(0)));
									 bloco->append(new LinearMove($3->getCoordX(), $3->getCoordY(), new Float(0)));
									 $$ = bloco;}
    ;

pinta
	: TOK_PINTA TOK_OPENP factor ',' factor TOK_CLOSEP ',' TOK_OPENP factor TOK_CLOSEP 	{		Stmts *bloco = new Stmts(new LinearMove($3, $5, new Float(1)));

																					for(int i=0; i<100; i++){
																						bloco->append(new LinearMove($3, $5));
																						bloco->append(new LinearMove($3, new BinaryOp($5, '+', $9)));
																						bloco->append(new LinearMove(new BinaryOp($3, '+', $9), new BinaryOp($5, '+', $9)));
																						bloco->append(new LinearMove(new BinaryOp($3, '+', $9), $5));
																						bloco->append(new LinearMove($3, $5));
																						$9 = new BinaryOp($9, '-', new Float(0.03));
																					 }
																					$$ = bloco;
																					}








arith_expr
	: arith_expr TOK_PLUS expr			{$$ = new BinaryOp($1, '+', $3);}
	| arith_expr TOK_MINUS expr			{$$ = new BinaryOp($1, '-', $3);}
	| factor 								{$$ = $1;}
	;


expr
	: expr TOK_MULTPL factor				{$$ = new BinaryOp($1, '*' , $3);}
	| expr TOK_DIVIDE factor				{$$ = new BinaryOp($1, '/' , $3);}
	|factor									{$$ = $1;}
	;
coordD
	: factor ',' factor {$$ = new Coord($1 , $3);}

	;

factor
	: TOK_OPENP arith_expr TOK_CLOSEP   {$$ = $2;  }
	|  TOK_INTEGER 	{ $$ = new Float($1); }
	;


%%

// CODIGO C

int yyerror(const char *s){
	printf("error: %s\n",s);
	return 0;
}

/*
int main(int argc, char *argv[]){
	if(argc > 1){
		yyin = fopen(argv[1], "r");
	
}	yyparse();
	if(yyin)
		fclose(yyin);
		
}
*/