%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "limite.c"


class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_WHILE TOK_IF TOK_ELSE
%token TOK_OPENP TOK_CLOSEP
%token TOK_INTEGER TOK_DOUBLE
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR
%token TOK_IDENT

%token TOK_INICIARCOORDS

%token TOK_LINE TOK_ARC


%token TOK_CIRCULO	
%token TOK_QUADRADO
%token TOK_TRIANGULO
%token TOK_RETANGULO
%token TOK_PENTAGONO
%token TOK_LOSANGO
%token TOK_HEXAGONO
%token TOK_TRAPEZIO

%union {
	int nint;
	float nfloat;
	char *ident;
	Node *node;
	Stmts *stmt;
}

%type <node> term expr factor stmt condblock elseblock whileblock logicexpr logicterm logicfactor TOK_AND TOK_OR 
%type <stmt> stmts figura
%type <nint> TOK_INTEGER
%type <nfloat> TOK_DOUBLE
%type <ident> TOK_IDENT


%nonassoc IFX
%nonassoc TOK_ELSE

%start programa

%%

programa : stmts    { Program p;
                      p.generate($1); }
		 ;

stmts : stmts stmt			{ $$->append($2); }			
	| stmt				{ $$ = new Stmts($1); }	
	  ;


stmt :	figura				{ $$ = $1; } 
	|condblock			{ $$ = new Capsule($1); }						
	| whileblock			{ $$ = new Capsule($1); }			
	| TOK_IDENT '=' expr ';' 	{ $$ = new Variable($1, $3); }					
	 ;




figura:    

TOK_INICIARCOORDS '(' ')' ';' 
		{ $$ = new Stmts(new Variable("x",new Float(0)));	
		  $$->append(new Variable("y", new Float(0)));
		  $$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));} 

|TOK_QUADRADO '(' '(' expr ',' expr ')' ',' expr ')' ';'
	
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4));
		$$->append(new Variable("y",$6)); 
		$$->append(new If(new CmpOp(new Load("x"), GT_OP, new Int16(4000)), ErroLimite() , NULL));

	

		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));
		$$->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '+', $9), new Float(0)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'+',$9)));
		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',$9)));
		$$->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '-', $9), new Float(0)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'-',$9))); }

|TOK_RETANGULO '(' '(' expr ',' expr ')' ',' expr ',' expr ')' ';'
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4));
		$$->append(new Variable("y",$6));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));
		$$->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '+', $11), new Float(0)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'+',$11)));
		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',$9)));
		$$->append(new LinearMove(new Load("x"),new BinaryOp(new Load("y"), '-', $11), new Float(0)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'-',$11))); }

							 			
|TOK_TRAPEZIO  '(' '(' '(' expr ',' expr ')' ',' expr ')' ',' '(' '(' expr ',' expr ')' ',' expr ')'  ')' ';'
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$5)); 
		$$->append(new Variable("y",$7)); 
		$$->append(new Variable("x2",$15)); 
		$$->append(new Variable("y2",$17));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $10), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$10)));
		$$->append(new LinearMove(new BinaryOp(new Load("x2"), '+', $20), new Load("y2"), new Float(0))); 
		$$->append(new Variable("x2",new BinaryOp(new Load("x2"),'+',$20)));
		$$->append(new LinearMove(new BinaryOp(new Load("x2"),'-',$20), new Load("y2"), new Float(0))); 
		$$->append(new Variable("x2",new BinaryOp(new Load("x2"),'-',$20)));
		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', $10), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',$10)));}

		

|TOK_LINE '(''(' expr ',' expr ')' ',' '(' expr ',' expr ')' ')' ';'	 	         
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4)); 
		$$->append(new Variable("y",$6)); 
		$$->append(new Variable("x2",$10)); 
		$$->append(new Variable("y2",$12));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		$$->append(new LinearMove(new Load("x2"), new Load("y2"), new Float(0)));
		$$->append(new Variable("x",new Load("x2")));
		$$->append(new Variable("y",new Load("y2")));}


|TOK_TRIANGULO  '(' '(' expr ',' expr ')' ',' '(' expr ',' expr ')' ',' '(' expr ',' expr ')' ')' ';'	
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4)); 
		$$->append(new Variable("y",$6)); 
		$$->append(new Variable("x2",$10)); 
		$$->append(new Variable("y2",$12));
		$$->append(new Variable("x3",$16));
		$$->append(new Variable("y3",$18));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		$$->append(new LinearMove(new Load("x2"), new Load("y2"), new Float(0)));
		$$->append(new LinearMove(new Load("x3"), new Load("y3"), new Float(0)));
		$$->append(new LinearMove(new Load("x"), new Load("x"), new Float(0)));}

|TOK_LOSANGO '(''(' expr ',' expr ')' ',' '(' expr ',' expr ')' ')' ';'	 	         
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4)); 
		$$->append(new Variable("y",$6)); 
		$$->append(new Variable("x2",$10)); 
		$$->append(new Variable("y2",$12));
		$$->append(new Variable("XDiferenca",new BinaryOp($10,'-',$4)));
		$$->append(new Variable("YDiferenca",new BinaryOp($12,'-',$6)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));
		$$->append(new LinearMove(new Load("x2"), new Load("y2"), new Float(0)));
		$$->append(new LinearMove(new Load("x"), new BinaryOp(new Load("y2"), '+', new Load("YDiferenca")), new Float(0))); 
		$$->append(new Variable("y2",new BinaryOp(new Load("y2"),'+',new Load("YDiferenca"))));
		$$->append(new LinearMove(new BinaryOp(new Load("x"),'-',new Load("XDiferenca")), new BinaryOp(new Load("y2"), '-', new Load("YDiferenca")), new Float(0)));
		$$->append(new Variable("y2",new BinaryOp(new Load("y2"),'-',new Load("YDiferenca"))));
		$$->append(new Variable("x",new BinaryOp(new Load("x2"),'-',new Load("XDiferenca"))));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));}



|TOK_PENTAGONO '(' '(' expr ',' expr ')' ',' expr ')' ';'
	
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4));
		$$->append(new Variable("y",$6)); 
		$$->append(new Variable("MetadeDoTamanho",new BinaryOp($9,'/',new Float(2))));
		$$->append(new Variable("OtantoPraVoltarPraMetade",new BinaryOp($9,'+',new Load("MetadeDoTamanho"))));
		
		//$$->append(new Variable("LadoDeCima",new BinaryOp(new Load("x"),'+',new BinaryOp($9,'/',new Float(2)))));
		
		
		


		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new BinaryOp(new Load("y"), '+', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'+',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', new Load("OtantoPraVoltarPraMetade")), new BinaryOp(new Load("y"), '+', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Load("OtantoPraVoltarPraMetade"))));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'+',$9)));




		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', new Load("OtantoPraVoltarPraMetade")), new BinaryOp(new Load("y"), '-', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Load("OtantoPraVoltarPraMetade"))));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'-',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new BinaryOp(new Load("y"), '-', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'-',$9)));}





|TOK_HEXAGONO '(' '(' expr ',' expr ')' ',' expr ')' ';'
	
		{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new Variable("x",$4));
		$$->append(new Variable("y",$6)); 
		

	

		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(1)));
		$$->append(new LinearMove(new Load("x"), new Load("y"), new Float(0)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new BinaryOp(new Load("y"), '+', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'+',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', $9), new BinaryOp(new Load("y"), '+', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',$9)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'+',$9)));


		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', $9), new Load("y"), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '-', $9), new BinaryOp(new Load("y"), '-', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'-',$9)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'-',$9)));

		$$->append(new LinearMove(new BinaryOp(new Load("x"), '+', $9), new BinaryOp(new Load("y"), '-', $9), new Float(0)));
		$$->append(new Variable("x",new BinaryOp(new Load("x"),'+',$9)));
		$$->append(new Variable("y",new BinaryOp(new Load("y"),'-',$9)));}

		

| TOK_CIRCULO '(' '(' expr ',' expr ')' ',' expr ')' ';'   
{ $$ = new Stmts(new LinearMove(new Load("x"), new Load("y"), new Float(1))); 
   $$->append(new LinearMove($4, $6, new Float(1)));
   $$->append(new LinearMove($4, $6, new Float(0)));
   $$->append((new Variable("x",$4)));
   $$->append((new Variable("y",$6)));
   $$->append(new ArcMove($4, $6, new Float(0), new Float(0) , $9));
						 
}
	;






condblock : TOK_IF '(' logicexpr ')' stmt %prec IFX		{ $$ = new If($3, $5, NULL); }		
		  | TOK_IF '(' logicexpr ')' stmt elseblock	{ $$ = new If($3, $5, $6); }			
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' %prec IFX	{ $$ = new If($3, $6, NULL); }	
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' elseblock	{ $$ = new If($3, $6, $8); }	
		  ;

elseblock : TOK_ELSE stmt			{ $$ = $2; }	
		  | TOK_ELSE '{' stmts '}'	{ $$ = $3; }	
		  ;

whileblock : TOK_WHILE '(' logicexpr ')' '{' stmts '}' { $$ = new While($3, $6); }
		   ;

logicexpr : logicexpr TOK_OR logicterm	{		        }	
		  | logicterm		{ $$ = new Capsule($1); }				
		  ;


logicterm : logicterm TOK_AND logicfactor {		        }
		  | logicfactor		  { $$ = new Capsule($1); }				
		  ;


logicfactor : '(' logicexpr ')'		{ $$ = new Capsule($2); }	
		| expr EQ_OP expr	{ $$ = new CmpOp($1, EQ_OP, $3); }	
		| expr NE_OP expr	{ $$ = new CmpOp($1, NE_OP, $3); }	
		| expr LE_OP expr	{ $$ = new CmpOp($1, LE_OP, $3); }	
		| expr GE_OP expr	{ $$ = new CmpOp($1, GE_OP, $3); }	
		| expr LT_OP expr	{ $$ = new CmpOp($1, LT_OP, $3); }	
		| expr GT_OP expr	{ $$ = new CmpOp($1, GT_OP, $3); }	
		;


expr : expr '+' term			{ $$ = new BinaryOp($1, '+', $3); }
	 | expr '-' term		{ $$ = new BinaryOp($1, '-', $3); }	
	 | term				{ $$ = $1; }	
	 ;

term : term '*' factor			{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' factor		{ $$ = new BinaryOp($1, '/', $3); }
	 | factor			{ $$ = $1; }	
	 ;

factor : '(' expr ')'			{ $$ = $2; }
	| TOK_IDENT			{ $$ = new Load($1); }
	| TOK_INTEGER			{ $$ = new Float($1); }
	| TOK_DOUBLE			{ $$ = new Float($1); }
	;


%%

// codigo C 

extern int yylineno;
extern char *yytext;
extern char *build_filename;

int yyerror(const char *s)
{
	fprintf(stderr, "%s:%d: error: %s %s\n", 
		build_filename, yylineno, s, yytext);
	exit(1);
}

extern "C" int yywrap() {
	return 1;
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
