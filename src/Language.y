%{
#include "Header.h"
#include "2018arm/nodeh_ext.h"

class Node;
class Stmts;

std::vector<AttachInterrupt *> vectorglobal;

%}

%token TOK_VOID TOK_FUNCTION TOK_RETURN
%token TOK_IF TOK_ELSE
%token TOK_FOR TOK_WHILE
%token TOK_PRINT
%token TOK_IN TOK_OUT TOK_STEPPER TOK_SERVO
%token TOK_DELAY TOK_AND TOK_OR
%token TOK_IDENTIFIER TOK_FLOAT TOK_INTEGER TOK_STRING TOK_TRUE TOK_FALSE
%token TOK_FINT TOK_FFLOAT TOK_FDOUBLE TOK_FCHAR TOK_FLONG TOK_FSHORT TOK_FUNSIGNED TOK_FBOOL

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
	ArrayElement ae;
	ArrayElements *aes;
	MatrixElement me;
	MatrixElements *mes;
	FunctionParam fp;
	FunctionParams *fps;
	ParamsCall *pc;
}

%type <node> term expr factor stmt condblock elseblock whileblock logicexpr logicterm logicfactor TOK_AND TOK_OR printstmt fe eventblock unary
%type <ae> element
%type <aes> elements relements
%type <fp> funcparam
%type <fps> funcparams
%type <pc> paramscall
%type <me> melement
%type <mes> matrix rmatrix
%type <node> funcblock returnblock
%type <stmt> stmts
%type <port> TOK_OUT TOK_IN
%type <nint> TOK_INTEGER
%type <nfloat> TOK_FLOAT
%type <ident> TOK_IDENTIFIER
%type <str> TOK_STRING
%type <nint> TOK_STEPPER
%type <nint> type_f

%precedence IFX
%precedence TOK_ELSE
%start programa

%%

programa : stmts    { Program p($1);
		 			  // interruptions setup
					  for(AttachInterrupt *a : vectorglobal) {
						$1->prepend(a);
					  }

					  /*std::fstream fs;
					  fs.open("ast.txt", std::fstream::out);
					  PrintAstVisitor(fs).visit(p);
					  fs.close();*/

					  p.generate(); 
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
	 | TOK_IDENTIFIER '[' expr ']' '=' expr ';'	{ $$ = new UpdateVector($1, $3, $6);} //Deixar para tratamento semantico, pois poderia aceitar uma expressão [a + 1]
	 | TOK_IDENTIFIER '(' paramscall ')' ';'	{ $$ = new FunctionCall($1, $3); }
	 | TOK_IDENTIFIER '+' '+' ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', new Int16(1))); }
	 | TOK_IDENTIFIER '+' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', $4)); }
	 | TOK_IDENTIFIER '-' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', $4)); }
	 | TOK_IDENTIFIER '*' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '*', $4)); }
	 | TOK_IDENTIFIER '=' relements ';'		{ $$ = new Vector($1, $3); } // name, size, expression
	 | TOK_IDENTIFIER '=' rmatrix ';'		{ $$ = new Matrix($1, $3);}
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

rmatrix : '{' matrix '}'				{ $$ = $2; }
	    ;

matrix : matrix ',' melement			{ $1->append($3);
										  $$ = $1;
										}
	   | melement						{ MatrixElements *mes = new MatrixElements();
										  mes->append($1);
										  $$ = mes;
										}
		
		;


melement : relements ':' TOK_INTEGER			{ MatrixElement me {$1, (unsigned)$3};
										  $$ = me;
										}
	   | relements						{ MatrixElement me {$1, 1};
										  $$ = me;
										}
	   ;
	 
relements : '{' elements '}'			{ $$ = $2;}
			;

elements : elements ',' element			{ $1->append($3);
											  $$ = $1;
											}
		   | element							{ ArrayElements *aes = new ArrayElements();
											  aes->append($1);
											  $$ = aes;
											}
		   ;

element : factor ':' TOK_INTEGER 				{ ArrayElement ae{$1, (unsigned)$3};
											  $$ = ae;
											}
       | factor							   	{ ArrayElement ae{$1, 1};
											  $$ = ae;
											}
	   ;

eventblock : TOK_QUANDO TOK_INTEGER TOK_ESTA TOK_INTEGER '{' stmts '}' 
		     {	
				char funcname[100];
				sprintf(funcname, "__callback_int_p%d_e%d", $2, $4);
				vectorglobal.push_back(new AttachInterrupt($2, funcname, $4));
				FunctionParams *fps = new FunctionParams();
				$$ = new FunctionDecl(0, funcname, fps, $6);
             }
		   ;

funcblock : type_f TOK_IDENTIFIER '(' funcparams ')' '{' stmts '}'		{ $$ = new FunctionDecl($1, $2, $4, $7); }
		  ;

funcparams: funcparams ',' funcparam {$1 -> append($3);
									  $$ = $1;
									  }
	      | funcparam { FunctionParams *fps = new FunctionParams();
						fps->append($1);
						$$ = fps;}
		  | %empty { FunctionParams *fps = new FunctionParams();
			  $$ = fps;
			}
		  ;

funcparam : type_f TOK_IDENTIFIER { FunctionParam fp{$2, $1}; 
									$$ = fp;}

type_f  : TOK_VOID { $$ = 0; }
		| TOK_FBOOL { $$ = 1; }
		| TOK_FSHORT TOK_FINT { $$ = 2; } 
		| TOK_FINT { $$ = 3; } 
		| TOK_FLONG TOK_FINT { $$ = 4; } 
		| TOK_FLONG TOK_FLONG TOK_FINT { $$ = 5; } 
		| TOK_FLONG TOK_FLONG TOK_FLONG TOK_FINT { $$ = 6; } 
		| TOK_FSHORT TOK_FFLOAT { $$ = 7; } 
		| TOK_FFLOAT { $$ = 8; } 
		| TOK_FDOUBLE { $$ = 9; } 
		| TOK_FDOUBLE TOK_FDOUBLE { $$ = 10; } 
	    ;

paramscall : paramscall ',' expr {$1 -> append($3);
								  $$ = $1;}
		   | expr { ParamsCall *pc = new ParamsCall();
		            pc->append($1);
				    $$ = pc;}
		   | %empty { ParamsCall *pc = new ParamsCall();
			   $$ = pc;
			 }
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
 /* 			| expr					{ $$ = new CmpOp($1, EQ_OP, new Int1(1));} */
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
	   | TOK_IDENTIFIER '[' expr ']'	{ $$ = new LoadVector($1, $3);} //Deixar para tratamento semantico, pois poderia aceitar uma expressão [a + 1]
	   | TOK_IDENTIFIER '[' expr ']' '[' expr ']'	{ $$ = new LoadMatrix($1, $3, $6);} //Deixar para tratamento semantico, pois poderia aceitar uma expressão [a + 1]
	   | TOK_TRUE				{ $$ = new Int1(1); }
	   | TOK_FALSE				{ $$ = new Int1(0); }
	   | TOK_INTEGER			{ $$ = new Int16($1); }
	   | TOK_FLOAT				{ $$ = new Float($1); }
	   | '(' TOK_FSHORT TOK_FINT ')' TOK_INTEGER	{ $$ = new Int8($5); } //Generate, Destty($2, $3), block, $5 .Make coersion
	   | '(' TOK_FLONG TOK_FINT ')' TOK_INTEGER	{ $$ = new Int32($5); } //Make coersion
	   | '(' TOK_FLONG TOK_FLONG TOK_FINT ')' TOK_INTEGER	{ $$ = new Int64($6); } //Make coersion
	   | '(' TOK_FFLOAT ')' TOK_FLOAT	{ $$ = new Float($4); } //Make coersion
       | '(' TOK_FDOUBLE ')' TOK_FLOAT	{ $$ = new Double($4); }  //Make coersion
	   | TOK_IN					{ $$ = new InPort($1); }
	   | TOK_IDENTIFIER '(' paramscall ')'	{ $$ = new FunctionCall($1, $3); }
       | unary					{ $$ = $1; }
	   ;

unary	: '-' factor		{ $$ = new BinaryOp($2, '*', new Int16(-1)); }
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

