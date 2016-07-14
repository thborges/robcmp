
#include <stdio.h>

void init() {};

void print(char t, void *data) {
	switch (t) {
		case 0: printf("Int: %d\n", *(short*)data); break;
		case 1: printf("Float: %f\n", *(float*)data); break;
		case 2: printf("String: %s\n", (char*)data); break;
	}
}

int analogRead(unsigned char t) {
	return getchar();
}

/*int main() {

	int r = 10;
	float d = 100.903;

	print(1, &d);
	print(0, &r);
}
*/
