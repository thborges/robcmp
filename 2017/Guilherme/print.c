#include <stdio.h>

void print(char t, void *data) {
	//printf("Chamou....\n");
	switch (t) {
		case 0:
			printf("%d", *(short*)data); 
			break;
		case 1:
			printf("%f", *(float*)data);
			break;
		case 2:
			printf("%s", (char*)data);
			break;
	}
}

