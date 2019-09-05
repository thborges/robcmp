#include "stepper_aux.h"

bool stepper_configured = false;
AccelStepper stepper_base(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
AccelStepper stepper_updown(AccelStepper::HALF4WIRE, 6, 8, 7, 9); 
AccelStepper stepper_forward(AccelStepper::HALF4WIRE, 10, 12, 11, 13);

#define SERVO_PORT A5
Servo servo_gripper;

void stepper_goto(int stepper, int pos) {
	if (!stepper_configured) {
    // Change these to suit your stepper if you want
    int maxSpeed = 4000;
    int speed = 10;
//    float acceleration = 100000;
    float acceleration = 1000;
    stepper_base.setMaxSpeed(maxSpeed);
    stepper_updown.setMaxSpeed(maxSpeed);
    stepper_forward.setMaxSpeed(maxSpeed);
    stepper_base.setAcceleration(acceleration);
    stepper_updown.setAcceleration(acceleration);
    stepper_forward.setAcceleration(acceleration);
		stepper_configured = true;
	}

	AccelStepper *s;
	if (stepper == 0)
		s = &stepper_base;
	else if (stepper == 1)
		s = &stepper_updown;
	else
		s = &stepper_forward;
	s->enableOutputs();
	s->runToNewPosition(pos);
	s->disableOutputs();
}

void servo_goto(int pos) {
	#define MIN_POS 82
	if (!servo_gripper.attached())
		servo_gripper.attach(SERVO_PORT);
	if (pos >= 0 && pos <= 38) {
		servo_gripper.write(pos + MIN_POS);
		delay(15); // small delay
	}
}

void print(char t, char *p) {
}

