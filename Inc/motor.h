#ifndef motor_h
#define motor_h

// define primitive functions
void pwm_init(void);
void analogWrite(int pin, int speed);

// Motor driver functions

void moveSteering(int speed, int steering);
void moveTank(int leftSpeed, int rightSpeed);
void moveForward(int speed);
void moveBackwards(int speed);
void moveLeftMotor(int speed);
void moveRightMotor(int speed);

#endif
