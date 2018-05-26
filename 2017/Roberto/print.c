#include <stdio.h>

void print(char t, void *data) {
        switch (t) {
                case 0:
                        printf("%d\n", *(short*)data);
                        break;
                case 1:
                        printf("%f\n", *(float*)data);
                        break;
                case 2:
                        printf("%s\n", (char*)data);
                        break;
         }
 }
 
