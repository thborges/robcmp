%{

%}

%locations
%define api.location.type {location_t}
%define api.pure full
%param {yyscan_t scanner}

%name-prefix="spec"
//%define api.prefix {spec} // not working in Bison 3.8.2

%code provides {
  #define YY_DECL int speclex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
}

%code top {
  #ifndef YYLTYPE
  #define YYLTYPE location_t
  #endif
  #include "FlexDependencies.h"
  #define SCANNER_OR_VISITOR
  #include "Header.h"
}

%union {
    // char *port;
	char *ident;
	char *str;


    Node *node;
	// Stmts *stmt;
	// vector<Node*> *nodes;

}

/* %union {
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
} */

%token SPEC_PORT SPEC_PORT_NAME SPEC_DIGITAL SPEC_BIND SPEC_IDENT SPEC_TO SPEC_XIDENT
%token SPEC_PWM SPEC_NAME SPEC_TRUE SPEC_FALSE SPEC_PORT_IDENT SPEC_STRING

/* %type <nodes> globals */
/* %type <node> global bind  */
%type <node>  bind 
%type <ident> SPEC_IDENT SPEC_XIDENT ident



%start program

%%

program : %empty
        | stmts
        ;

stmts : stmts stmt
    | stmt
    ;

stmt : bind 
    /* | port_statement */
    ;


bind : SPEC_BIND ident[id] SPEC_TO ident[to] ';' {
    injections.insert({$to, make_pair(string($id), BindScope(bs_singleton))});
}

ident : SPEC_IDENT 
	| SPEC_XIDENT
	;

/* port_statement : SPEC_PORT_NAME '{' port_attributes '}'
    ;

port_attributes : port_attributes port_attribute
    | port_attribute
    ;

port_attribute : attribute_digital
    | attribute_pwm
    | port_bind
    ;

attribute_digital : SPEC_DIGITAL '=' SPEC_TRUE
    | SPEC_DIGITAL '=' SPEC_FALSE
    ;

attribute_pwm : SPEC_PWM '=' SPEC_TRUE
    | SPEC_PWM '=' SPEC_FALSE
    ;

port_bind : SPEC_BIND '=' SPEC_IDENT {  }
    ; */


%%

extern char *spec_filename;
extern int errorsfound;

void specerror(YYLTYPE *loc, yyscan_t yyscanner, const char *s)
{
	fprintf(stderr, "%s:%d: error: %s\n", spec_filename, loc->first_line, s);
	errorsfound++;
}

