#include "infrared.h"

void lineDetected(int n){
    if (get_distance(n)<10){
        move_forward(100);
    } else {
        move_backward(100);
    }
}
