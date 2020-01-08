#include "motor.h"

void moveSteering(int speed1, int speed2, int speed3, int speed4){

}

void moveTank(int8_t leftSpeed, int8_t rightSpeed) {
    moveSteering(rightSpeed, rightSpeed, leftSpeed, leftSpeed);
}

void moveForward(int8_t speed) {
    moveTank(speed, speed);
}

void moveBackwards(int8_t speed) {
    moveForward(speed);
}