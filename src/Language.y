%{

#include <stdlib.h>
#include <limits.h>
#include "Header.h"
#include "2018arm/nodeh_ext.h"

class Node;
class Stmts;

Node* getNodeForIntConst(int64_t i);
std::vector<AttachInterrupt *> vectorglobal;

extern int errorsfound;

%}

%define parse.error verbose

%token TOK_VOID TOK_RETURN TOK_REGISTER TOK_AT TOK_VOLATILE TOK_CONST
%token TOK_IF TOK_ELSE
%token TOK_LOOP TOK_WHILE
%token TOK_PRINT
%token TOK_IN TOK_OUT TOK_STEPPER TOK_SERVO
%token TOK_DELAY TOK_AND TOK_OR
%token TOK_IDENTIFIER TOK_FLOAT TOK_DOUBLE TOK_LDOUBLE TOK_INTEGER TOK_STRING TOK_TRUE TOK_FALSE
%token TOK_FINT8 TOK_FINT16 TOK_FINT32 TOK_FINT64
%token TOK_FFLOAT TOK_FDOUBLE TOK_FCHAR TOK_FLONG TOK_FUNSIGNED TOK_FBOOL

%token TOK_QUANDO TOK_ESTA
%token EQ_OP NE_OP GE_OP LE_OP GT_OP LT_OP TOK_LSHIFT TOK_RSHIFT

%union {
	char *port;
	char *ident;
	char *str;
	int64_t nint;
	float nfloat;
	double ndouble;
	long double nldouble;
	Node *node;
	Stmts *stmt;
	ArrayElement ae;
	ArrayElements *aes;
	MatrixElement me;
	MatrixElements *mes;
	FunctionParam fp;
	FunctionParams *fps;
	ParamsCall *pc;
	LanguageDataType dt;
}

%type <node> term term2 expr factor stmt gstmt condblock elseblock whileblock logicexpr
%type <node> logicterm logicfactor TOK_AND TOK_OR printstmt fe eventblock unary
%type <node> funcblock returnblock registerstmt cast
%type <ae> element
%type <aes> elements relements
%type <fp> funcparam
%type <fps> funcparams
%type <pc> paramscall
%type <me> melement
%type <mes> matrix rmatrix
%type <stmt> stmts gstmts
%type <port> TOK_OUT TOK_IN
%type <nint> TOK_INTEGER
%type <nfloat> TOK_FLOAT
%type <ndouble> TOK_DOUBLE
%type <nldouble> TOK_LDOUBLE
%type <ident> TOK_IDENTIFIER
%type <str> TOK_STRING
%type <nint> TOK_STEPPER
%type <dt> type_f registertype

%precedence IFX
%precedence TOK_ELSE
%start programa

%%

programa : gstmts	{ Program p($1);
		 			  // interruptions setup
					  for(AttachInterrupt *a : vectorglobal) {
						$1->prepend(a);
					  }

					  /*std::fstream fs;
					  fs.open("ast", std::fstream::out);
					  PrintAstVisitor(fs).visit(p);
					  fs.close();*/
					  if (errorsfound == 0)
						  p.generate(); 
                    };
		 ;

gstmts : gstmts gstmt       { $1->append($2); }
	   | gstmt				{ $$ = new Stmts($1); }
	   ;

gstmt : TOK_IDENTIFIER '=' expr ';'					{ $$ = new Scalar($1, $3, qnone); }
	  | TOK_CONST TOK_IDENTIFIER '=' expr ';'		{ $$ = new Scalar($2, $4, qconst); }
	  | TOK_VOLATILE TOK_IDENTIFIER '=' expr ';'	{ $$ = new Scalar($2, $4, qvolatile); }
	  | TOK_IDENTIFIER '=' relements ';'			{ $$ = new Array($1, $3); } // name, size, expression
	  | TOK_IDENTIFIER '=' rmatrix ';'				{ $$ = new Matrix($1, $3);}
	  | registerstmt ';'							{ $$ = $1; }
	  | fe											{ $$ = $1; }
	  | error ';'									{ /* ignora o erro ate o proximo ';' */
													  $$ = new Int8(0); // evita falha de segmentacao
													};

fe : funcblock	{ $$ = $1; } 
   | eventblock	{ $$ = $1; } 
   ;

funcblock : type_f TOK_IDENTIFIER '(' funcparams ')' ';' {
				$$ = new FunctionDeclExtern($1, $2, $4);
			}
		  | type_f TOK_IDENTIFIER '(' funcparams ')' '{' stmts '}' {
				$$ = new FunctionDecl($1, $2, $4, $7); 
			}
		  ;

eventblock : TOK_QUANDO TOK_INTEGER TOK_ESTA TOK_INTEGER '{' stmts '}' {	
				char funcname[100];
				snprintf(funcname, 100, "__callback_int_p%lld_e%lld", $2, $4);
				vectorglobal.push_back(new AttachInterrupt($2, funcname, $4));
				FunctionParams *fps = new FunctionParams();
				$$ = new FunctionDecl(tvoid, funcname, fps, $6);
             }
		   ;

stmts : stmts stmt	{ $1->append($2);
	  				  $$ = $1; }
	  | stmt		{ $$ = new Stmts($1); }
	  ;

stmt : gstmt									{ $$ = $1; }
	 | TOK_OUT '=' expr ';'						{ $$ = new OutPort($1, $3); } 
	 | TOK_IDENTIFIER '(' paramscall ')' ';'	{ $$ = new FunctionCall($1, $3); }
	 | TOK_IDENTIFIER '+' '+' ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', new Int8(1))); }
	 | TOK_IDENTIFIER '-' '-' ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', new Int8(1))); }
	 | TOK_IDENTIFIER '+' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', $4)); }
	 | TOK_IDENTIFIER '-' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', $4)); }
	 | TOK_IDENTIFIER '*' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '*', $4)); }
	 | TOK_IDENTIFIER '/' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '/', $4)); }
	 | TOK_IDENTIFIER '|' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '|', $4)); }
	 | TOK_IDENTIFIER '&' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '&', $4)); }
	 | TOK_IDENTIFIER '^' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '^', $4)); }
	 | TOK_DELAY expr';'						{ $$ = new Delay($2); }
	 | condblock								{ $$ = $1; }
	 | whileblock								{ $$ = $1; }
	 | returnblock ';'							{ $$ = $1; }
	 | printstmt ';'							{ $$ = $1; }
	 | TOK_STEPPER expr ';'						{ $$ = new StepperGoto($1, $2); }
	 | TOK_SERVO expr ';'						{ $$ = new ServoGoto($2); }
	 | TOK_IDENTIFIER '[' expr ']' '=' expr ';'	{ $$ = new UpdateArray($1, $3, $6);} //Deixar para tratamento semantico, pois poderia aceitar uma expressão [a + 1]
	 | TOK_IDENTIFIER '[' expr ']' '[' expr ']' '=' expr ';'	{ $$ = new UpdateMatrix($1, $3, $6, $9); }

rmatrix : '{' matrix '}'				{ $$ = $2; }
	    ;

matrix : matrix ',' melement			{ $1->append($3);
										  $$ = $1; }
	   | melement						{ MatrixElements *mes = new MatrixElements();
										  mes->append($1);
										  $$ = mes; }
	   ;


melement : relements ':' TOK_INTEGER	{ MatrixElement me {$1, (unsigned)$3};
										  $$ = me; }
	     | relements					{ MatrixElement me {$1, 1};
										  $$ = me; }
	     ;
	 
relements : '{' elements '}'			{ $$ = $2; }
		  ;

elements : elements ',' element			{ $1->append($3);
										  $$ = $1; }
		 | element						{ ArrayElements *aes = new ArrayElements();
										  aes->append($1);
										  $$ = aes; }
		 ;

element : factor ':' TOK_INTEGER		{ ArrayElement ae{$1, (unsigned)$3};
										  $$ = ae; }
        | factor						{ ArrayElement ae{$1, 1};
										  $$ = ae; }
	    ;

funcparams: funcparams ',' funcparam {
				$1 -> append($3);
				$$ = $1; 
			}
	      | funcparam {
				FunctionParams *fps = new FunctionParams();
				fps->append($1);
				$$ = fps; 
			}
		  | %empty {
				FunctionParams *fps = new FunctionParams();
				$$ = fps;
			}
		  ;

funcparam : type_f TOK_IDENTIFIER {
				FunctionParam fp{$2, $1}; 
				$$ = fp;
			}

type_f  : TOK_VOID { $$ = tvoid; }
		| TOK_FCHAR { $$ = tchar; }
		| TOK_FBOOL { $$ = tbool; }
		| TOK_FINT8 { $$ = tint8; } 
		| TOK_FINT16 { $$ = tint16; } 
		| TOK_FINT32 { $$ = tint32; } 
		| TOK_FINT64 { $$ = tint64; } 
		| TOK_FUNSIGNED TOK_FINT8 { $$ = tint8u; } 
		| TOK_FUNSIGNED TOK_FINT16 { $$ = tint16u; } 
		| TOK_FUNSIGNED TOK_FINT32 { $$ = tint32u; } 
		| TOK_FUNSIGNED TOK_FINT64 { $$ = tint64u; } 
		| TOK_FFLOAT { $$ = tfloat; } 
		| TOK_FDOUBLE { $$ = tdouble; } 
		| TOK_FLONG TOK_FDOUBLE { $$ = tldouble; } 
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

whileblock : TOK_WHILE '(' logicexpr ')' '{' stmts '}'	{ $$ = new While($3, $6); }
		   | TOK_LOOP '{' stmts '}' 					{ $$ = new Loop($3); }
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
	 | expr '|' term			{ $$ = new BinaryOp($1, '|', $3); }
	 | expr TOK_LSHIFT term		{ $$ = new BinaryOp($1, TOK_LSHIFT, $3); }
	 | expr TOK_RSHIFT term		{ $$ = new BinaryOp($1, TOK_RSHIFT, $3); }
	 | term						{ $$ = $1; }
	 ;

term : term '*' term2		{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' term2		{ $$ = new BinaryOp($1, '/', $3); }
	 | term '%' term2		{ $$ = new BinaryOp($1, '%', $3); }
	 | term '^' term2		{ $$ = new BinaryOp($1, '^', $3); }
	 | term2				{ $$ = $1; }
	 ;

term2 : term2 '&' factor    { $$ = new BinaryOp($1, '&', $3); }
	  | factor				{ $$ = $1; }
	  ;

factor : '(' expr ')'			{ $$ = $2; }
	   | TOK_IDENTIFIER			{ $$ = new Load($1); }
	   | TOK_IDENTIFIER '[' expr ']'				{ $$ = new LoadArray($1, $3);} 
	   | TOK_IDENTIFIER '[' expr ']' '[' expr ']'	{ $$ = new LoadMatrix($1, $3, $6);} 
	   | TOK_TRUE				{ $$ = new Int1(1); }
	   | TOK_FALSE				{ $$ = new Int1(0); }
	   | TOK_INTEGER			{ $$ = getNodeForIntConst($1); }
	   | TOK_FLOAT				{ $$ = new Float($1); }
	   | TOK_DOUBLE				{ $$ = new Double($1); }
	   | TOK_LDOUBLE			{ $$ = new Float128($1); }
	   | TOK_IN					{ $$ = new InPort($1); }
	   | TOK_IDENTIFIER '(' paramscall ')'	{ $$ = new FunctionCall($1, $3); }
	   | unary { $$ = $1; }
	   ;

unary : '-' factor	{ $$ = new BinaryOp($2, '*', getNodeForIntConst(-1)); }
	  | '~' factor	{ $$ = new FlipOp($2); }
	  | cast		{ $$ = $1; }
      ;

cast : '(' type_f ')' factor { $$ = new Cast($2, $4); }
	 ;

printstmt : TOK_PRINT TOK_STRING		{ $$ = new Print(new String($2)); }
		  | TOK_PRINT expr				{ $$ = new Print($2); }

registerstmt : TOK_REGISTER registertype TOK_IDENTIFIER TOK_AT expr {
				 $$ = new Pointer($3, $2, $5, true);
			   }
			 ;

registertype : TOK_FINT8	{ $$ = tint8; }
			 | TOK_FINT16	{ $$ = tint16; }
			 | TOK_FINT32	{ $$ = tint32; }
			 | TOK_FINT64	{ $$ = tint64; }
			 ;
%%

extern int yylineno;
extern int yycolno;
extern char *yytext;
extern char *build_filename;

int yyerror(const char *s)
{
	fprintf(stderr, "%s:%d:%d: %s\n", 
		build_filename, yylineno, yycolno, s);
	errorsfound++;
	return 0;
	//exit(1);
}

Node* getNodeForIntConst(int64_t i) {
	if (i >= SCHAR_MIN && i <= SCHAR_MAX)
		return new Int8(i);
	else if (i >= SHRT_MIN && i <= SHRT_MAX)
		return new Int16(i);
	else if (i >= INT_MIN && i <= INT_MAX)
		return new Int32(i);
	else
		return new Int64(i);
}

extern "C" int yywrap() {
	return 1;
}

