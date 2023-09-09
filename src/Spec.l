%{

#include "Header.h"
#include "bison_Spec.hpp"

extern void unescape(char *s);

%}

%option prefix="spec"

%option yylineno

D	[0-9]
L	[a-zA-Z]

%%


[ \t\n\r]                             { /* espaços */ }

"port"                                { return SPEC_PORT; }
"digital"                             { return SPEC_DIGITAL; }
"pwm"                                 { return SPEC_PWM; }
"name"                                { return SPEC_NAME; }

"bind"                                { return SPEC_BIND; }

"true"                                { return SPEC_TRUE; } 
"false"                               { return SPEC_FALSE; }

"to"                                  { return SPEC_TO; }

\"[^\"]+\"                            { speclval.str = strndup(yytext+1, yyleng-2); unescape(speclval.str); return SPEC_STRING; }

"{"                                   { return '{'; }
"}"                                   { return '}'; }

"="                                   { return '='; }
":"                                   { return ':'; }

{L}({L}|{D})*                         { return SPEC_PORT_NAME; }


{L}({L}|{D})*\.*({L}|{D})*             { return SPEC_IDENT; }

.                                     { specerror("lexical error, caractere nao pertence ao alfabeto da linguagem:"); }

%%

