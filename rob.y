%{
#include "node.h"

class Node;
%}

%token TOK_IDENT TOK_IN TOK_OUT TOK_FLOAT TOK_INTEIRO TOK_PRINT TOK_DELAY 
%token TOK_IF TOK_ELSE TOK_WHILE
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR

%union {
	char *port;
	char *ident;
	char *number;
	Node *node;
}

%type <node> term expr factor stmt stmts condblock elseblock whileblock logicexpr logicterm logicfactor TOK_AND TOK_OR 
%type <port> TOK_OUT TOK_IN
%type <number> TOK_INTEIRO TOK_FLOAT
%type <ident> TOK_IDENT

%nonassoc IFX
%nonassoc TOK_ELSE
%start programa

%%

programa : stmts    { Program p;
                      p.generate($1); }
		 ;

stmts : stmts stmt			{ $$ = new Stmts($1, $2); }
	  | stmt				{ $$ = new Stmts($1); }
	  ;

stmt : TOK_OUT '=' expr ';'				{ $$ = new OutPort($1, $3); } 
	 | TOK_IDENT '=' expr ';'			{ $$ = new Variable($1, $3); }
	 | TOK_DELAY expr';'        		{ $$ = new Delay($2); }
	 | condblock						{ $$ = new Capsule($1); }
	 | whileblock						{ $$ = new Capsule($1); }
	 /* | TOK_PRINT TOK_IDENT ';'		{ $$ = new_print($2); } */
	 ;

condblock : TOK_IF '(' logicexpr ')' stmt %prec IFX				{ $$ = new If($3, $5, NULL); }
		  | TOK_IF '(' logicexpr ')' stmt elseblock				{ $$ = new If($3, $5, $6); }
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' %prec IFX	{ $$ = new If($3, $6, NULL); }
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' elseblock	{ $$ = new If($3, $6, $8); }
		  ;

elseblock : TOK_ELSE stmt				{ $$ = $2; }
		  | TOK_ELSE '{' stmts '}'		{ $$ = $3; }
		  ;

whileblock : TOK_WHILE '(' logicexpr ')' '{' stmts '}' { $$ = new While($3, $6); }
		   ;

logicexpr : logicexpr TOK_OR logicterm		{  }
		  | logicterm						{ $$ = new Capsule($1); }
		  ;

logicterm : logicterm TOK_AND logicfactor	{  }
		  | logicfactor						{ $$ = new Capsule($1); }
		  ;

logicfactor : '(' logicexpr ')'		{ $$ = new Capsule($2); }
			| expr EQ_OP expr		{ $$ = new CmpOp($1, EQ_OP, $3); }
			| expr NE_OP expr		{ $$ = new CmpOp($1, NE_OP, $3); }
			| expr LE_OP expr		{ $$ = new CmpOp($1, LE_OP, $3); }
			| expr GE_OP expr		{ $$ = new CmpOp($1, GE_OP, $3); }
			| expr LT_OP expr		{ $$ = new CmpOp($1, LT_OP, $3); }
			| expr GT_OP expr		{ $$ = new CmpOp($1, GT_OP, $3); }
			;

expr : expr '+' term		{ $$ = new BinaryOp($1, '+', $3); }
	 | expr '-' term		{ $$ = new BinaryOp($1, '-', $3); }
	 | term					{ $$ = new Capsule($1); }
	 ;

term : term '*' factor		{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' factor		{ $$ = new BinaryOp($1, '/', $3); }
	 | factor				{ $$ = new Capsule($1); }
	 ;

factor : '(' expr ')'		{ $$ = new Capsule($2); }
	   | TOK_IDENT			{ $$ = new Load($1); }
	   | TOK_INTEIRO		{ $$ = new Int16($1); }
	   | TOK_FLOAT			{ $$ = new Float($1); }
	   | TOK_IN				{ $$ = new InPort($1); }
	   ;

%%

extern int yylineno;
extern char *yytext;
extern char *build_filename;

void yyerror(const char *s)
{
	fprintf(stderr, "%s:%d: error: %s %s\n", 
		build_filename, yylineno, s, yytext);
	exit(1);
}

extern "C" int yywrap() {
	return 1;
}

