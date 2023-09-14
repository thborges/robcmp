%{

class Node;
class Stmts;


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
}

%union {
    // char *port;
	// char *ident;
	char *str;


    // Node *node;
	// Stmts *stmt;
}


%token SPEC_PORT SPEC_PORT_NAME SPEC_DIGITAL SPEC_BIND SPEC_IDENT SPEC_TO
%token SPEC_PWM SPEC_NAME SPEC_TRUE SPEC_FALSE SPEC_PORT_IDENT SPEC_STRING


%start program

%%

program : stmts
    ;

stmts : stmts stmt
    | stmt
    ;

stmt : bind 
    | port_statement
    ;

bind : SPEC_BIND SPEC_IDENT SPEC_TO SPEC_IDENT
    ;

port_statement : SPEC_PORT_NAME '{' port_attributes '}'
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
    ;


%%

extern char *spec_filename;
extern int errorsfound;

void specerror(YYLTYPE *loc, yyscan_t yyscanner, const char *s)
{
	fprintf(stderr, "%s:%d: error: %s\n", spec_filename, loc->first_line, s);
	errorsfound++;
}

