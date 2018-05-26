%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "roman.h"

class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_PRINT TOK_WHILE TOK_IF TOK_ELSE
%token TOK_PLUS TOK_MINUS TOK_MULTPL TOK_DIVIDE
%token TOK_OPENP TOK_CLOSEP
%token TOK_INTEGER TOK_DOUBLE
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR
%token TOK_EQUALS TOK_IDENT

%union {
	int nint;
	float nfloat;
	char *ident;
	Node *node;
	Stmts *stmt;
}

%type <node> term expr factor stmt condblock elseblock whileblock logicexpr logicterm logicfactor TOK_AND TOK_OR printstmt
%type <stmt> stmts
%type <nint> TOK_INTEGER
%type <nfloat> TOK_DOUBLE
%type <ident> TOK_IDENT


//%type <stmt> stmts
//%type <nint> TOK_INTEGER
//%type <ident> TOK_IDENT

%nonassoc IFX
%nonassoc TOK_ELSE

%start programa

%%


programa : stmts    { Program p;
                      p.generate($1); }
		 ;

stmts : stmts stmt			{ $$->append($2); }			
	  | stmt			{ $$ = new Stmts($1); }	
	  ;


stmt :	condblock			{ $$ = new Capsule($1); }						
	 | whileblock			{ $$ = new Capsule($1); }			
	 | printstmt ';'		{ $$ = $1; }
	| TOK_IDENT '=' expr ';' 	{ $$ = new Variable($1, $3); }					
	 ;



condblock : TOK_IF '(' logicexpr ')' stmt %prec IFX		{ $$ = new If($3, $5, NULL); }		
		  | TOK_IF '(' logicexpr ')' stmt elseblock	{ $$ = new If($3, $5, $6); }			
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' %prec IFX	{ $$ = new If($3, $6, NULL); }	
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' elseblock	{ $$ = new If($3, $6, $8); }	
		  ;

elseblock : TOK_ELSE stmt			{ $$ = $2; }	
		  | TOK_ELSE '{' stmts '}'	{ $$ = $3; }	
		  ;

whileblock : TOK_WHILE '(' logicexpr ')' '{' stmts '}' 
		   ;

logicexpr : logicexpr TOK_OR logicterm		
		  | logicterm						
		  ;


logicterm : logicterm TOK_AND logicfactor
		  | logicfactor						
		  ;


logicfactor : '(' logicexpr ')'		
		| expr EQ_OP expr		
		| expr NE_OP expr		
		| expr LE_OP expr		
		| expr GE_OP expr		
		| expr LT_OP expr		
		| expr GT_OP expr		
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
	| TOK_INTEGER			{ $$ = new Int16($1); }
	| TOK_DOUBLE			{ $$ = new Float($1); }
	;

printstmt: TOK_PRINT expr	{printf("Passou\n"); $$ = decimalToarabic($2); }	
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
