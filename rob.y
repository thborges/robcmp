%{
#include "node.h"
#include "funcoes.h"


class Node;
class Stmts;

%}

%token  TOK_AGUARDE
%token  TOK_RETANGULO TOK_DESENHA_UFG EQ_OP


%union {
	char *port;
	char *ident;
	char *str;
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;
}

%type <node> stmt  
%type <stmt> stmts

%nonassoc IFX

%start programa

%%

programa : stmts    { Program p;
                      p.generate($1); }
		 ;

stmts : stmts stmt			{ $$->append($2); }
	  | stmt				{ $$ = new Stmts($1); }
	  ;

stmt : 	TOK_RETANGULO 			 			{ $$ = RETANGULO(); }
		| TOK_AGUARDE						{ $$ = AGUARDE (); }
		| TOK_DESENHA_UFG					{ $$ = UFG(); }	
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

