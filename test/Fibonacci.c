#include <stdio.h>

int fibonacci (int n){
	if (n == 1)
		return 1;
	else
		if (n == 2)
			return 1;
		else
		{
			return fibonacci(n - 1) + fibonacci(n - 2);
		}
	return 1;
}

void main (){
	printf ("%d\n",fibonacci(1));
	printf ("%d\n",fibonacci(2));
	printf ("%d\n",fibonacci(3));
	printf ("%d\n",fibonacci(4));
	printf ("%d\n",fibonacci(5));
}
