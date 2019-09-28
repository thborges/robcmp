%{
#include "Header.h"
#include "2018arm/nodeh_ext.h"

class Node;
class Stmts;

std::vector<AttachInterrupt *> vectorglobal;

%}

%token TOK_FUNCTION TOK_RETURN
%token TOK_IF TOK_ELSE
%token TOK_FOR TOK_WHILE
%token TOK_PRINT
%token TOK_IN TOK_OUT TOK_STEPPER TOK_SERVO
%token TOK_DELAY TOK_AND TOK_OR
%token TOK_IDENTIFIER TOK_FLOAT TOK_INTEGER TOK_STRING

%token TOK_QUANDO TOK_ESTA
%token EQ_OP NE_OP GE_OP LE_OP GT_OP LT_OP

%union {
	char *port;
	char *ident;
	char *str;
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;
}

%type <node> term expr factor stmt condblock elseblock whileblock logicexpr logicterm logicfactor TOK_AND TOK_OR printstmt fe eventblock
%type <node> funcblock returnblock
%type <node> rmultivalue multivalue value
%type <stmt> stmts
%type <port> TOK_OUT TOK_IN
%type <nint> TOK_INTEGER
%type <nfloat> TOK_FLOAT
%type <ident> TOK_IDENTIFIER
%type <str> TOK_STRING
%type <nint> TOK_STEPPER

%nonassoc IFX
%nonassoc TOK_ELSE
%start programa

%%

programa : stmts    { Program p;
		 			  // interruptions setup
					  for(AttachInterrupt *a : vectorglobal) {
						$1->prepend(a);
					  }
					  p.generate($1); 
                    };
		 ;

stmts : stmts stmt			{ $1->append($2);
	  						  $$ = $1; 
							}
	  | stmt				{ $$ = new Stmts($1); }
	  ;

fe : funcblock 						{ $$ = $1; } 
   | eventblock						{ $$ = $1; } 
   ;


stmt : TOK_OUT '=' expr ';'					{ $$ = new OutPort($1, $3); } 
	 | TOK_IDENTIFIER '=' expr ';'			{ $$ = new Scalar($1, $3); }
	 | TOK_IDENTIFIER '=' rmultivalue ';'	{ $$ = new Vector($1, 2, $3); } // name, size, expression
	 | TOK_DELAY expr';'					{ $$ = new Delay($2); }
	 | condblock							{ $$ = $1; }
	 | whileblock							{ $$ = $1; }
	 | fe									{ $$ = $1; }
	 | returnblock ';'						{ $$ = $1; }
	 | printstmt ';'						{ $$ = $1; }
	 | TOK_STEPPER expr ';'					{ $$ = new StepperGoto($1, $2); }
	 | TOK_SERVO expr ';'					{ $$ = new ServoGoto($2); }
	 | error ';'						    { /* ignora o erro ate o proximo ';' */
											  $$ = new Return(new Int16(0)); // evita falha de segmentacao
											}
	 ;
	 
rmultivalue : '[' multivalue ']' { $$ = $2; }
			;

multivalue : multivalue ',' value { }
		   | value { $$ = $1; }
		   ;

value : factor ':' TOK_INTEGER { }
	  | factor { $$ = $1; }
	  ;

eventblock : TOK_QUANDO TOK_INTEGER TOK_ESTA TOK_INTEGER '{' stmts '}' 
		     {	
				char funcname[100];
				sprintf(funcname, "__callback_int_p%d_e%d", $2, $4);
				vectorglobal.push_back(new AttachInterrupt($2, funcname, $4));
				$$ = new FunctionDecl(funcname, $6);
             }
		   ;

funcblock : TOK_FUNCTION TOK_IDENTIFIER '(' ')' '{' stmts '}'		{ $$ = new FunctionDecl($2, $6); }
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

logicexpr : logicexpr TOK_OR logicterm		{ $$ = new BinaryOp($1, TOK_OR, $3); }
		  | logicterm						{ $$ = $1; }
		  ;

logicterm : logicterm TOK_AND logicfactor	{ $$ = new BinaryOp($1, TOK_AND, $3); }
		  | logicfactor						{ $$ = $1; }
		  ;

logicfactor : '(' logicexpr ')'		{ $$ = $2; }
			| expr '=''=' expr		{ $$ = new CmpOp($1, EQ_OP, $4); }
			| expr '!''=' expr		{ $$ = new CmpOp($1, NE_OP, $4); }
			| expr '<''=' expr		{ $$ = new CmpOp($1, LE_OP, $4); }
			| expr '>''=' expr		{ $$ = new CmpOp($1, GE_OP, $4); }
			| expr '<' expr			{ $$ = new CmpOp($1, LT_OP, $3); }
			| expr '>' expr			{ $$ = new CmpOp($1, GT_OP, $3); }
			;

expr : expr '+' term			{ $$ = new BinaryOp($1, '+', $3); }
	 | expr '-' term			{ $$ = new BinaryOp($1, '-', $3); }
	 | term						{ $$ = $1; }
	 ;

term : term '*' factor		{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' factor		{ $$ = new BinaryOp($1, '/', $3); }
	 | term '%' factor		{ $$ = new BinaryOp($1, '%', $3); }
	 | factor				{ $$ = $1; }
	 ;

factor : '(' expr ')'			{ $$ = $2; }
	   | TOK_IDENTIFIER			{ $$ = new Load($1); }
	   | TOK_IDENTIFIER '[' TOK_INTEGER ']'	{ $$ = new LoadVector($1, $3);} //Deixar para tratamento semantico, pois poderia aceitar uma expressão [a + 1]
	   | TOK_INTEGER			{ $$ = new Int16($1); }
	   | TOK_FLOAT				{ $$ = new Float($1); }
	   | TOK_IN					{ $$ = new InPort($1); }
	   | TOK_IDENTIFIER '(' ')'	{ $$ = new FunctionCall($1); }
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

