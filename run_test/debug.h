
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

void onexit(void) __attribute__ ((destructor));
void refresh_screen();
void init();
void print(char t, void *data);
int analogRead(unsigned char t);
void analogWrite(char port, short value);
void delay(int milis);
void stepper_goto(int stepper, int pos);
void servo_goto(int pos);

