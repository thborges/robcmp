#include <stdio.h>
#include <float.h>

extern "C" void linear_move(float x, float y, float z) {
	if ((x == FLT_MAX) && (y == FLT_MAX))
		printf("G01 Z%f\n", z);
	else if (z == FLT_MAX)
		printf("G01 X%f Y%f\n", x, y);
	else
		printf("G01 X%f Y%f Z%f\n", x, y, z);
}

extern "C" void arc_move(float x, float y, float z, float i, float j) {

	if (z == FLT_MAX)
		printf("G02 X%f Y%f I%f J%f\n", x, y, i, j);
	else
		printf("G02 X%f Y%f Z%f I%f J%f\n", x, y, z, i, j);
}

extern "C" void init() {

}


