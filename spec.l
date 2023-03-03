%{


%}

%%

[ \t\n\r]              { /* espaços */ }

"port"                 { return TOK_PORT; }
"port_name"            { return TOK_PORT_NAME; }
"digital"              { return TOK_DIGITAL; }
"pwm"                  { return TOK_PWM; }
"name"                 { return TOK_NAME; }

/* "True"                 { return TOK_TRUE; }  */
/* "False"                { return TOK_FALSE; } */

"A"[0-9]+               { }

.                       { yyerror("lexical error, caractere nao pertence ao alfabeto da linguagem:"); }


%%
