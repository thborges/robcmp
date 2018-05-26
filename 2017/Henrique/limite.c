#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

Node* ErroLimite()
{
	yyerror("Valor passou de 40");
	return new Float(-1);
}
