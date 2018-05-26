%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

class Node;
class Stmts;

extern FILE *yyin;

%}

%token TOK_Q TOK_L TOK_C TOK_T TOK_R TOK_T_E TOK_Q_P
%token TOK_PLUS TOK_MINUS TOK_MULTPL TOK_DIVIDE TOK_LADO TOK_RAIO TOK_ALT TOK_LARG
%token TOK_OPENP TOK_CLOSEP TOK_CABELO TOK_BRACO
%token TOK_INTEGER TOK_FLOAT
%token EQ_OP NE_OP LT_OP GT_OP LE_OP GE_OP TOK_AND TOK_OR TOK_C_P

%union {
	int nint;
	float nfloat;
	Node *node;
	Stmts *stmt;
}

%type <node> factor programa linha quadrado circulo circulo_p triangulo triangulo_eq retangulo cabelo braco quadrado_p stmt 
%type <node> arith_expr term
%type <stmt> stmts
%type <nint> TOK_INTEGER
%type <nfloat> TOK_FLOAT

%start programa

%%

programa 
	: stmts {Program p; 
	         p.generate($1); }
	;

stmts 
	: stmts stmt 	{ $1->append($2); }
	| stmt		   	{ $$ = new Stmts($1); }

stmt
	: linha ';'                                   { $$ = new Capsule($1); }
	| quadrado ';'                                { $$ = new Capsule($1); }
	| circulo ';'                                 { $$ = new Capsule($1); }
	| triangulo ';'                               { $$ = new Capsule($1); }
	| retangulo ';'                               { $$ = new Capsule($1); }
	| cabelo ';'								  { $$ = new Capsule($1); }
	| triangulo_eq ';'							  { $$ = new Capsule($1); }
	| braco ';' 								  { $$ = new Capsule($1); }
	| quadrado_p ';' 					       	  { $$ = new Capsule($1); }
	| circulo_p ';' 					       	  { $$ = new Capsule($1); }
	;

linha
	:TOK_L TOK_OPENP factor ',' factor '|' factor ',' factor TOK_CLOSEP          { 	
																					Stmts *linha = new Stmts(new LinearMove($3, $5, new Float(1)));
																					linha->append(new LinearMove($3, $5));
																					linha->append(new LinearMove($7, $9));
																					$$ = linha;
																					}

quadrado
	: TOK_Q TOK_OPENP factor ',' factor '|' TOK_LADO '=' factor TOK_CLOSEP 	{		Stmts *quadrado = new Stmts(new LinearMove($3, $5, new Float(1)));																				
																					quadrado->append(new LinearMove($3, $5));
																					quadrado->append(new LinearMove($3, new BinaryOp($5, '+', $9)));
																					quadrado->append(new LinearMove(new BinaryOp($3, '+', $9), new BinaryOp($5, '+', $9)));
																					quadrado->append(new LinearMove(new BinaryOp($3, '+', $9), $5));
																					quadrado->append(new LinearMove($3, $5));
																					 
																					$$ = quadrado;
																					}

quadrado_p
	: TOK_Q_P TOK_OPENP factor ',' factor '|' TOK_LADO '=' factor TOK_CLOSEP 	{	Stmts *quadrado_p = new Stmts(new LinearMove($3, $5, new Float(1)));
																					Node* qtd = new BinaryOp($9, '/', new Float(300.0));
																					for(int i=0; i<300; i++){
																						$9 = new BinaryOp($9, '-', qtd);
																						quadrado_p->append(new LinearMove($3, $5));
																						quadrado_p->append(new LinearMove($3, new BinaryOp($5, '+', $9)));
																						quadrado_p->append(new LinearMove(new BinaryOp($3, '+', $9), new BinaryOp($5, '+', $9)));
																						quadrado_p->append(new LinearMove(new BinaryOp($3, '+', $9), $5));
																						quadrado_p->append(new LinearMove($3, $5));
																					 }
																					$$ = quadrado_p;
																					}

circulo
	: TOK_C TOK_OPENP factor ',' factor '|' TOK_RAIO '=' factor TOK_CLOSEP       {  Stmts *circulo = new Stmts(new LinearMove($3, $5, new Float(1)));
																					circulo->append(new LinearMove($3, $5)); 
																					circulo->append(new ArcMove($3, $5, 0, $9, 0));
																					$$ = circulo;
																				 }

circulo_p
	: TOK_C_P TOK_OPENP factor ',' factor '|' TOK_RAIO '=' factor TOK_CLOSEP       {  Stmts *circulo_p = new Stmts(new LinearMove($3, $5, new Float(1)));
																					  Node* qtd = new BinaryOp($9, '/', new Float(300.0));
																					  for(int i=0; i<300; i++){
																						  $9 = new BinaryOp($9, '-', qtd);
																						  circulo_p->append(new LinearMove($3, $5)); 
																					  	  circulo_p->append(new ArcMove($3, $5, 0, $9, 0));
																					  }
																					  $$ = circulo_p;
																				  }

triangulo
	: TOK_T TOK_OPENP factor ',' factor '|' factor ',' factor '|' factor ',' factor TOK_CLOSEP   {  
																									Stmts *triangulo = new Stmts(new LinearMove($3, $5, new Float(1)));
																									triangulo->append(new LinearMove($3, $5));
																									triangulo->append(new LinearMove($7, $9));
																									triangulo->append(new LinearMove($11, $13));
																									triangulo->append(new LinearMove($3, $5));
																									$$ = triangulo;
																									}

triangulo_eq
	: TOK_T_E TOK_OPENP factor ',' factor '|' factor ',' factor TOK_CLOSEP		{  
																				   Stmts *triangulo_eq = new Stmts(new LinearMove($3, $5, new Float(1)));
																				   triangulo_eq->append(new LinearMove($3, $5));
																				   triangulo_eq->append(new LinearMove($7, $9));
																				   triangulo_eq->append(new LinearMove($3, $5));
																				   Node* distPontos = new BinaryOp($7, '-', $3);
																				   Node* distX = new BinaryOp(distPontos, '/', new Float(2));
																				   Node* topoY = new BinaryOp($5, '+', distPontos);
																				   Node* topoX = new BinaryOp(distX, '+', $3);
																				   triangulo_eq->append(new LinearMove(topoX, topoY));
																				   triangulo_eq->append(new LinearMove($7, $9));
																				   $$ = triangulo_eq;
																				   }

retangulo
	: TOK_R TOK_OPENP factor ',' factor '|' TOK_LARG '=' factor '|' TOK_ALT '=' factor TOK_CLOSEP	{  Stmts *retangulo = new Stmts(new LinearMove($3, $5, new Float(1)));
																									   retangulo->append(new LinearMove($3, $5));																				
																								       retangulo->append(new LinearMove($3, new BinaryOp($5, '+', $13)));
																								       retangulo->append(new LinearMove(new BinaryOp($3, '+', $9), new BinaryOp($5, '+', $13)));
																								       retangulo->append(new LinearMove(new BinaryOp($3, '+', $9), $5));
																								       retangulo->append(new LinearMove($3, $5));
																								       $$ = retangulo;
	 																							    }
																									   
cabelo
	: TOK_CABELO TOK_OPENP factor ',' factor '|' factor ',' factor '|' TOK_ALT '=' factor '|' TOK_INTEGER TOK_CLOSEP   {  Stmts *cabelo = new Stmts(new LinearMove($3, $5, new Float(1)));																				
																														  cabelo->append(new LinearMove($3, $5));	   
																														  cabelo->append(new LinearMove($7, $9));
																										                  cabelo->append(new LinearMove($3, $5));
																														  Node* distPontos = new BinaryOp($7, '-', $3); // CALCULA A DIFERENÇA ENTRE OS 2 PONTOS
																														  Node* qtd = new Int32($15); // TRANSFORMA O INT EM NÓ 
																														  Node* intervalo = new BinaryOp(distPontos, '/', qtd); // INTERVALO DE PONTOS NO EIXO X	 
																														  for(int i=1; i<=$15; i++){
																															 Node* count = new Int32(i); // TRANSFORMA O i EM NODE P/ FAZER OPERAÇÕES 
																															 Node* defX = new BinaryOp(intervalo, '*', count);
																															 cabelo->append(new LinearMove(new BinaryOp(defX, '+', $3), new BinaryOp($5, '+', $13)));
																															 cabelo->append(new LinearMove(new BinaryOp(defX, '+', $3), $5));
																										                }
																										                $$ = cabelo;
																									                    }

braco
	: TOK_BRACO TOK_OPENP factor ',' factor '|' factor ',' factor '|' factor ',' factor '|' factor ',' factor TOK_CLOSEP 	{   Stmts *braco = new Stmts(new LinearMove($3, $5, new Float(1)));
																														  		braco->append(new LinearMove($3, $5));
																														  		braco->append(new LinearMove($7, $9));
																														  		braco->append(new LinearMove($3, $5, new Float(1))); // VOLTA P DESENHAR OUTRO PONTO
																														  		braco->append(new LinearMove($11, $13));
																														  		braco->append(new LinearMove($15, $17));
																													      		braco->append(new LinearMove($7, $9));
																														  		$$ = braco;
																														  	}


arith_expr
	: arith_expr TOK_PLUS term				{ $$ = new BinaryOp($1, '+', $3);}
    | arith_expr TOK_MINUS term				{ $$ = new BinaryOp($1, '-', $3);}
    | arith_expr TOK_DIVIDE term			{ $$ = new BinaryOp($1, '/', $3);}
	| factor 								{ $$ = $1;}
	; 
 
term 
	: term TOK_MULTPL factor				{ $$ = new BinaryOp($1, '*' , $3);}
	| term TOK_DIVIDE factor				{ $$ = new BinaryOp($1, '/' , $3);}
	| factor								{ $$ = $1;}
	;

factor
	:  TOK_OPENP arith_expr TOK_CLOSEP   	{ $$ = $2;  }
	|  TOK_INTEGER 							{ $$ = new Float($1); }
	|  TOK_FLOAT 							{ $$ = new Float($1); }
	;


%%

// codigo c

int yyerror(const char *s){
      printf("erro: %s \n", s);
      return 0; 
}

/*int main (int argc, char *argv[]){
      if (argc > 1){
          yyin = fopen(argv[1], "r");
      }
     yyparse();
     if (yyin)
         fclose(yyin); 
}
*/
