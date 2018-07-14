#ifndef STEPPER_AUXH
#define STEPPER_AUXH

#include "AccelStepper.h"
#include "Servo.h"

#ifdef __cplusplus
extern "C" {
#endif

void stepper_goto(int stepper, int pos);
void servo_goto(int pos);
void print(char t, char *p);

#ifdef __cplusplus
}
#endif

#endif
