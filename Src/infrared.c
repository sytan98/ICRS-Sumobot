#include "infrared.h"

void lineDetected(int n){
    if (getDistance(n)<10){
        moveForward(100);
    } else {
        moveBackwards(100);
    }
}
