%{

#include "Header.h"

class Node;
class Stmts;


%}


%define api.prefix {spec}

%union {
    // char *port;
	// char *ident;
	// char *str;


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

extern int speclineno;
extern char *spectext;
extern char *spec_filename;
extern int errorsfound;

int specerror(const char *s)
{
	fprintf(stderr, "%s:%d: error: %s %s\n", spec_filename, speclineno, s, spectext);
	errorsfound++;
	return 0;
}

extern "C" int specwrap() {
    return 1;
}