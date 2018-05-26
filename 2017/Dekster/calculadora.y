%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

class Node;
class Stmts;

extern FILE *yyin;

%}


%token TOK_PLUS TOK_MINUS TOK_MULTPL TOK_DIVIDE
%token TOK_OPENP TOK_CLOSEP
%token TOK_INTEGER TOK_DOUBLE
%token NE_OP EQ_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR
%token TOK_ALTURA TOK_BASE TOK_RETANGULO TOK_CIRCULO TOK_RAIO TOK_DM TOK_dM TOK_ID TOK_LOSANGO TOK_LINHA TOK_IGUAL

%union {
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;

	Coord *coordenada;
}

%type <node> term arith_expr factor programa figura stmt lx ly
%type <stmt> stmts
%type <nint> TOK_INTEGER
%type <nfloat> TOK_DOUBLE 
%type <coordenada> coord

%start programa

%%

programa : stmts	{Program p; p.generate($1); }
	;
stmts 	:stmts stmt	{ $$-> append($2); }
	|stmt		{ $$ = new Stmts($1); }

stmt	:arith_expr ';'		
	|figura 	 { $$ = $1; }					
	;

coord	:TOK_OPENP TOK_DOUBLE ','  TOK_DOUBLE TOK_CLOSEP	{ $$ = new Coord(new Float($2), new Float($4)); } 

figura	:TOK_LINHA  coord TOK_ID coord ';'
	{
		Stmts *s = new Stmts(
		new LinearMove(
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(10)));

		s->append(
			new LinearMove(
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(0)));
		s->append(
			new LinearMove(
				$4->getCoordx(),
				$4->getCoordy(),
				new Float(0)));

	$$ = s;
	}

	|TOK_CIRCULO coord TOK_RAIO TOK_OPENP TOK_DOUBLE TOK_CLOSEP ';'
	{

		
		Stmts *s = new Stmts(
		new LinearMove(
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(10)));
	s->append(
		new LinearMove(
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(0)));
				
	s->append(
		new ArcMove(
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(0),
				new Float($5),
				new Float(0)));



	$$ = s;

				
				
		}


	|TOK_LOSANGO coord TOK_DM TOK_OPENP TOK_DOUBLE TOK_CLOSEP TOK_dM TOK_OPENP TOK_DOUBLE TOK_CLOSEP ';'
	{
		Node *lx = new BinaryOp($2->getCoordx(),'+', new Float($5));
			
		Node *ly = new BinaryOp($2->getCoordy(),'+', new Float($9));

		Stmts *s = new Stmts(
		new LinearMove( $2->getCoordx(),
				$2->getCoordy(),
				new Float(10)));
		s->append(
			new LinearMove(
				$2->getCoordx(),
				new BinaryOp(ly,'/', new Float(2)),
				new Float(0)));
		s->append(
			new LinearMove(
				new BinaryOp(lx,'/', new Float(2)),
				$2->getCoordy(),
				new Float(0)));
		s->append(
			new LinearMove(
				new BinaryOp($2->getCoordx(),'+', new Float($5)),
				new BinaryOp(ly,'/', new Float(2)),
				new Float(0)));
		s->append(
			new LinearMove(
				new BinaryOp(lx,'/', new Float(2)),
				new BinaryOp($2->getCoordy(),'+', new Float($9)),
				new Float(0)));
		s->append(
			new LinearMove(
				$2->getCoordx(),
				new BinaryOp(ly,'/', new Float(2)),
				new Float(0)));

		$$ = s;

	}	
	|TOK_RETANGULO coord TOK_BASE TOK_OPENP TOK_DOUBLE TOK_CLOSEP TOK_ALTURA TOK_OPENP TOK_DOUBLE TOK_CLOSEP ';'
	 { 
		Stmts *s = new Stmts(
		new LinearMove(	$2->getCoordx(),
				$2->getCoordy(),
				new Float(10)));
		s->append( 
			new LinearMove( 
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(0)));

		s->append( 
			new LinearMove( 
				new BinaryOp($2->getCoordx(),'+', new Float($5)),
				$2->getCoordy(),
				new Float(0)));
		s->append(
			new LinearMove(
				new BinaryOp($2->getCoordx(),'+', new Float($5)),
				new BinaryOp($2->getCoordy(),'+', new Float($9)),
				new Float(0)));
		s->append(
			new LinearMove(
				$2->getCoordx(),
				new BinaryOp($2->getCoordy(),'+', new Float($9)),
				new Float(0)));
		s->append(
			new LinearMove(
				$2->getCoordx(),
				$2->getCoordy(),
				new Float(0)));
		$$ = s;
	}
 


arith_expr
	: arith_expr TOK_PLUS term	{ $$ = new BinaryOp($1, '+', $3); }
	| arith_expr TOK_MINUS term	{ $$ = new BinaryOp($1, '-', $3); }
	| term				{ $$ = $1; }
	;

term
	: term TOK_MULTPL factor	{ $$ = new BinaryOp($1, '*', $3); }
	| term TOK_DIVIDE factor	{ $$ = new BinaryOp($1, '/', $3); }
	|factor				{ $$ = $1; }
	;

factor
	: TOK_OPENP arith_expr TOK_CLOSEP	{$$ = $2; }
	| TOK_INTEGER				{$$ = new Int32($1); }
	| TOK_DOUBLE				{$$ = new Float($1); }
	;

%%

//codigo c

int yyerror(const char *s) {
	printf("error: %s\n",s);
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
