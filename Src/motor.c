#include "motor.h"

void moveSteering(int speed1, int speed2, int speed3, int speed4){

}

void moveSimple(int leftSpeed, int rightSpeed) {
    moveSteering(rightSpeed, rightSpeed, leftSpeed, leftSpeed);
}

