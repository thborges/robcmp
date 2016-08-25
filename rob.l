%{

#include "node.h"
#include "bison.hpp"

extern void unescape(char *s);

%}

%option yylineno
%x COMMENT

%%

[ \t\n\r]				{ /* espaços */ }
"/*"					{ yymore(); BEGIN COMMENT; }
<COMMENT>[^*]			{ yymore(); }
<COMMENT>"*"/[^/]		{ yymore(); }
<COMMENT>"*/"			{ BEGIN(INITIAL); }

"//".*$					{ fprintf(stderr, "Comentario: %s\n", yytext); /* comentario de linha */}

"print"					{ return(TOK_PRINT); }

"entrada"[0-9]+			{ yylval.port = strndup(yytext+7, yyleng-7);
						  return(TOK_ENTRADA);
						}

"desenha1"				{ return(TOK_DESENHA_1); }
"desenha2"				{ return(TOK_DESENHA_2); }
"desenha3"				{ return(TOK_DESENHA_3); }
"desenha4"				{ return(TOK_DESENHA_4); }
"desenha5"				{ return(TOK_DESENHA_5); }
"desenha6"				{ return(TOK_DESENHA_6); }
"desenha7"			 	{ return(TOK_DESENHA_7); }
"proximo"				{ return(TOK_ESPACAMENTO); }
"delay"					{ return(TOK_DELAY); }
"if"					{ return(TOK_IF); }
"else"					{ return(TOK_ELSE); }
"enquanto"				{ return(TOK_ENQUANTO); }
"RESOLVA"				{ return(TOK_RESOLVA); }
"=="					{ return(EQ_OP); }
"!="					{ return(NE_OP); }
"<="					{ return(LE_OP); }
">="					{ return(GE_OP); }
">"					{ return(GT_OP); }
"<"					{ return(LT_OP); }


[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.ident = strndup(yytext, yyleng); 
						  return(TOK_IDENT); }

"("						{ return('('); }
")"						{ return(')'); }
"{"						{ return('{'); }
"}"						{ return('}'); }


-?[0-9]+				{ yylval.nint = atoi(yytext);
						  return(TOK_INTEIRO); }

"*"						{ return('*'); }
"/"						{ return('/'); }
"+"						{ return('+'); }
"-"						{ return('-'); }
"="						{ return('='); }
";"						{ return(';'); }

\"([^\\\"]|\\.)*\"		{ yylval.str = strndup(yytext+1, yyleng-2);
						  unescape(yylval.str);
						  return(TOK_STRING); }

%%


