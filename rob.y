%{
#include "node.h"
#include "2018arm/nodeh_ext.h"

class Node;
class Stmts;
%}

%token TOK_IDENT TOK_IN TOK_OUT TOK_FLOAT TOK_INTEIRO TOK_PRINT TOK_DELAY 
%token TOK_IF TOK_ELSE TOK_WHILE
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR
%token TOK_STRING
%token TOK_STEPPER TOK_SERVO
%token TOK_FUNC TOK_RETURN

%union {
	char *port;
	char *ident;
	char *str;
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;
}

%type <node> term expr factor stmt condblock elseblock whileblock logicexpr logicterm logicfactor TOK_AND TOK_OR printstmt
%type <node> funcblock returnblock
%type <stmt> stmts
%type <port> TOK_OUT TOK_IN
%type <nint> TOK_INTEIRO
%type <nfloat> TOK_FLOAT
%type <ident> TOK_IDENT
%type <str> TOK_STRING
%type <nint> TOK_STEPPER

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

stmt : TOK_OUT '=' expr ';'				{ $$ = new OutPort($1, $3); } 
	 | TOK_IDENT '=' expr ';'			{ $$ = new Variable($1, $3); }
	 | TOK_DELAY expr';'				{ $$ = new Delay($2); }
	 | condblock						{ $$ = $1; }
	 | whileblock						{ $$ = $1; }
	 | funcblock 						{ $$ = $1; } 
	 | returnblock ';'					{ $$ = $1; }
	 | printstmt ';'					{ $$ = $1; }
	 | TOK_STEPPER expr ';'				{ $$ = new StepperGoto($1, $2); }
	 | TOK_SERVO expr ';'				{ $$ = new ServoGoto($2); }
	 | error ';'                        { /* ignora o erro ate o proximo ';' */ }
	 ;

funcblock : TOK_FUNC TOK_IDENT '(' ')' '{' stmts '}'		{ $$ = new FunctionDecl($2, $6); }
		  ;

returnblock : TOK_RETURN expr			{ $$ = new Return($2); }
			| TOK_RETURN logicexpr		{ $$ = new Return($2); }
			;

condblock : TOK_IF '(' logicexpr ')' stmt %prec IFX				{ $$ = new If($3, $5, NULL); }
		  | TOK_IF '(' logicexpr ')' stmt elseblock				{ $$ = new If($3, $5, $6); }
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' %prec IFX		{ $$ = new If($3, $6, NULL); }
		  | TOK_IF '(' logicexpr ')' '{' stmts '}' elseblock		{ $$ = new If($3, $6, $8); }
		  ;

elseblock : TOK_ELSE stmt				{ $$ = $2; }
		  | TOK_ELSE '{' stmts '}'		{ $$ = $3; }
		  ;

whileblock : TOK_WHILE '(' logicexpr ')' '{' stmts '}' { $$ = new While($3, $6); }
		   ;

logicexpr : logicexpr TOK_OR logicterm		{ $$ = new BinaryOp($1, TOK_OR, $2); }
		  | logicterm						{ $$ = new Capsule($1); }
		  ;

logicterm : logicterm TOK_AND logicfactor	{ $$ = new BinaryOp($1, TOK_AND, $2); }
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

expr : expr '+' term			{ $$ = new BinaryOp($1, '+', $3); }
	 | expr '-' term			{ $$ = new BinaryOp($1, '-', $3); }
	 | term					{ $$ = $1; }
	 ;

term : term '*' factor		{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' factor		{ $$ = new BinaryOp($1, '/', $3); }
	 | factor				{ $$ = $1; }
	 ;

factor : '(' expr ')'		{ $$ = $2; }
	   | TOK_IDENT			{ $$ = new Load($1); }
	   | TOK_INTEIRO		{ $$ = new Int16($1); }
	   | TOK_FLOAT			{ $$ = new Float($1); }
	   | TOK_IN				{ $$ = new InPort($1); }
	   | TOK_IDENT '(' ')'	{ $$ = new FunctionCall($1); }
	   ;

printstmt : TOK_PRINT TOK_STRING		{ $$ = new Print(new String($2)); }
		  | TOK_PRINT expr				{ $$ = new Print($2); }
%%

extern int yylineno;
extern char *yytext;
extern char *build_filename;
extern int errorsfound;

int yyerror(const char *s)
{
	fprintf(stderr, "%s:%d: error: %s %s\n", 
		build_filename, yylineno, s, yytext);
	errorsfound++;
	return 0;
	//exit(1);
}

extern "C" int yywrap() {
	return 1;
}

