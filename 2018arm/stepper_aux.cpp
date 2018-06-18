#include "stepper_aux.h"

AccelStepper stepper_base(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper stepper_updown(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
AccelStepper stepper_forward(AccelStepper::HALF4WIRE, 6, 8, 7, 9);

void stepper_goto(int stepper, int pos) {
	AccelStepper *s;
	if (stepper == 1)
		s = &stepper_base;
	else if (stepper == 2)
		s = &stepper_updown;
	else
		s = &stepper_forward;
	s->enableOutputs();
	s->runToNewPosition(pos);
	s->disableOutputs();
}

