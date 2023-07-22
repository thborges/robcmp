
%locations
%define api.location.type {location_t}
%define api.pure full
%define parse.error verbose
%param {yyscan_t scanner}

%code top {
  #include <stdlib.h>
  #include <limits.h>
  #include "Header.h"
}

%code provides {
  #ifndef YYLTYPE
  #define YYLTYPE location_t
  #endif
}

%token TOK_VOID TOK_RETURN TOK_REGISTER TOK_AT TOK_VOLATILE TOK_CONST TOK_ASM
%token TOK_IF TOK_ELSE
%token TOK_LOOP TOK_WHILE
%token TOK_PRINT
%token TOK_IN TOK_OUT TOK_STEPPER TOK_SERVO
%token TOK_DELAY TOK_AND TOK_OR
%token TOK_IDENTIFIER TOK_FLOAT TOK_DOUBLE TOK_LDOUBLE TOK_INTEGER TOK_STRING TOK_TRUE TOK_FALSE
%token TOK_FINT8 TOK_FINT16 TOK_FINT32 TOK_FINT64
%token TOK_FFLOAT TOK_FDOUBLE TOK_FCHAR TOK_FLONG TOK_FUNSIGNED TOK_FBOOL
%token TOK_TYPE TOK_INTF TOK_IMPL TOK_USE

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
	BasicDataType dt;
	Field field;
	Structure *structure;
	ComplexIdentifier *complexIdent;
	vector<Node*> *nodes;
	vector<string> *strings;
}

%start programa
