#ifndef motor_h
#define motor_h
#include <stdint.h>

void moveSteering(int speed1, int speed2, int speed3, int speed4);
// function will scale -100 to 100
void moveTank(int8_t rightSpeed, int8_t leftSpeed);
void moveForward(int8_t speed);
void moveBackwards(int8_t speed);
void moveLeft(int8_t speed);
void moveRight(int8_t speed);

#endif
