%{

#include "FlexDependencies.h"
#include "Spec_y.hpp"

extern void unescape(char *s);
void specerror(YYLTYPE *loc, yyscan_t yyscanner, const char *s);

%}

%option noinput nounput noyywrap
%option yylineno
%option reentrant bison-locations
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

\"[^\"]+\"                            { yylval->str = strndup(yytext+1, yyleng-2); unescape(yylval->str); return SPEC_STRING; }

"{"                                   { return '{'; }
"}"                                   { return '}'; }

"="                                   { return '='; }
":"                                   { return ':'; }

{L}({L}|{D})*                         { return SPEC_PORT_NAME; }


{L}({L}|{D})*\.*({L}|{D})*             { return SPEC_IDENT; }

.                                     { specerror(yylloc, NULL, "lexical error, caractere nao pertence ao alfabeto da linguagem:"); }

%%

