#include "infrared.h"

void lineDetected(int n){
    // TODO: update getDistance to accept single int argument only
    // TODO: Create new function getSingleClosestEnemy in distance.c
    // (maybe) create a function that handles when the enemy is NE/NW/SE/SW and
    // use it in both infrared.c and in main.c
    int enemyLocation = 12;//getSingleClosestEnemy();
    float distance = 0.05; //getDistance(n);

    // if line detected is NE
    if (n == 1) {
        // and enemy is NE, BAMBOOZLED! so continue NE
        if ((enemyLocation == 1 || enemyLocation == 2) && distance < 5) {
            moveTank(100, 75);
        } else { // actual line, so move backwards
            moveTank(-100, -90);
        }
    }

    // if line detected is SE
    if (n == 2) {
        // and enemy is behind us, rotate clockwise
        if ((enemyLocation == 3 || enemyLocation == 4) && distance < 5) {
            moveTank(75, -75);
        } else { // actual line, so move forwards
            moveTank(90, 100);
        }
    }

    // if line detected is SW
    if (n == 3) {
        // and enemy is behind us, rotate anti-clockwise
        if ((enemyLocation == 5 || enemyLocation == 6) && distance < 5) {
            moveTank(-75, 75);
        } else { // actual line, so move forwards
            moveTank(100, 90);
        }
    }

    // if line detected is NW
    if (n == 4) {
        // and enemy is in front of us, push NW
        if ((enemyLocation == 7 || enemyLocation == 8) && distance < 5) {
            moveTank(75, 100);
        } else { // actual line, so move backwards
            moveTank(-100, -90);
        }
    }

}
