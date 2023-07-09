#include <stdio.h>

void funct(int a){
	printf ("%d", a);
}

void main(){
	int x = 5;
	printf ("%d\n", x);
	funct(x);

	printf ("%d\n", x);
	int y;
	funct(y);



}

