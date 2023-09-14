
%locations
%define api.location.type {location_t}
%define api.pure full
%define parse.lac full
%param {yyscan_t scanner}

%code top {
  #include <stdlib.h>
  #include <limits.h>
  #define SCANNER_OR_VISITOR
  #include "Header.h"
}

%code provides {
  #ifndef YYLTYPE
  #define YYLTYPE location_t
  #endif
  #include "FlexDependencies.h"
}

%token TOK_VOID TOK_RETURN TOK_REGISTER TOK_AT TOK_VOLATILE TOK_CONST TOK_ASM
%token TOK_IF TOK_ELSE
%token TOK_LOOP TOK_WHILE
%token TOK_AND TOK_OR
%token TOK_IDENTIFIER TOK_XIDENTIFIER
%token TOK_FLOAT TOK_DOUBLE TOK_LDOUBLE TOK_INTEGER TOK_STRING TOK_TRUE TOK_FALSE
%token TOK_FINT8 TOK_FINT16 TOK_FINT32 TOK_FINT64
%token TOK_FFLOAT TOK_FDOUBLE TOK_FCHAR TOK_FLONG TOK_FUNSIGNED TOK_FBOOL
%token TOK_TYPE TOK_INTF TOK_IMPL TOK_USE TOK_ENUM

%token TOK_BIND TOK_TO TOK_SINGLETON TOK_TRANSIENT

%token TOK_QUANDO TOK_ESTA
%token EQ_OP NE_OP GE_OP LE_OP GT_OP LT_OP TOK_LSHIFT TOK_RSHIFT

%union {
	char *ident;
	char *str;
	int64_t nint;
	float nfloat;
	double ndouble;
	long double nldouble;
	Node *node;
	ArrayElements *aes;
	MatrixElements *mes;
	FunctionParams *fps;
	ParamsCall *pc;
	vector<Node*> *nodes;
	vector<string> *strings;
	ArrayElement *ae;
	MatrixElement *me;
	FunctionParam *fp;
}

%start programa
