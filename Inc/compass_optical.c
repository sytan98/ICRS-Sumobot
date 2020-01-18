#include <stdio.h>
#include <math.h>

/* orientation and position variables */
// Heading - the position of our robot
// startAngle - initial position our robot is facing
float heading, startAngle;
// xycoords: the x,y coordinates of our robot on the field.
// will have to measure the field and set this to a reasonable value before the competition.
static float xycoords[2] = {0,0};
// polar coords: coordinates measured in r, theta.
static float polarcoords[2] = {0,0};

/* orientation and position functions */
// gets the relative heading of the robot from compass readings
float getHeading(float angle);
// updates the x,y position of the robot
void updatePos(float hdg, int dx, int dy);
// gets the polar coordinates of the current xy pos
void updatePolarCoords(void);
/* distance sensor filtering variables */

// holds the max expected readings for each distance sensor.
// indexed clockwise from robot 12'o clock:
// 0: FR-TOF, 1: R-US, 2: RR-US, 3: LR-US, 4: L-US, 5: FL-TOF.
static float maxSensorRange[6];

/* distance sensor filtering functions */
// uses the global heading and x,y position variables to update the above array
void updateMaxSensorRange(float hdg, int rightTofAngle, int leftTofAngle);

int main() {

    // testing goes here
    startAngle = 0;

    updatePos(0, 10, 10);
    printf("current pos: %f, %f\n", xycoords[0], xycoords[1]);
    updatePolarCoords();
    printf("current polar pos: r:%f, theta:%f\n", polarcoords[0], polarcoords[1]);
    return 0;
}

// Angle is the reading of the compass sensor
// heading and starting directions defined beforehand as globals
float getHeading(float angle){
    heading = angle - startAngle;
    if(heading < 0){
        heading += 360;
    }
    return heading;
}

// Do we need to init a trigo function LUT?
// Remember to include and link math.h
void updatePos(float hdg, int dx, int dy){
    float deltaX, deltaY;

    hdg = hdg*M_PI/180; // Convert degrees into radians
    // printf("Heading is %f, PI is %f\n", hdg, M_PI);

    // taking into account change in X position
    deltaX = dx*sin(hdg);
    deltaY = dx*cos(hdg);
    xycoords[0] += deltaX;
    xycoords[1] += deltaY;

    // taking into account change in Y position
    hdg += M_PI/2;
    deltaX = dy*sin(hdg);
    deltaY = dy*cos(hdg);
    xycoords[0] += deltaX;
    xycoords[1] += deltaY;

}

void updatePolarCoords(void){
    // atan(y/x) gives theta in RADIANS
    polarcoords[1] = atan2(xycoords[1], xycoords[0]);
    // pythagoras' theorem
    polarcoords[0] = sqrt(xycoords[0]*xycoords[0] + xycoords[1]*xycoords[1]);
}


// takes into account the TOF sensor angle to give a proper reading
// Have to see the orientation of the TOF servos!
// Current assumption: TOF sensor ranges from 45-135.
// 90 is dead center. 45 is full left, and 135 is full right.
void updateMaxSensorRange(float hdg, int rightTofAngle, int leftTofAngle){

}